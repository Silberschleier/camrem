//
// Created by Christopher Schmidt on 03.08.15.
//

#include "Context.h"

Http::Context::Context(MHD_Connection *connection, const char *uri, const char *method) : uri_(uri), method_(method) {
    headers_ = json::object();
    getdata_ = json::object();
    cookies_ = json::object();
    postdata_ = "";

    MHD_get_connection_values(connection, MHD_GET_ARGUMENT_KIND, Context::process_connection_values, this);
    MHD_get_connection_values(connection, MHD_HEADER_KIND, Context::process_connection_values, this);
    MHD_get_connection_values(connection, MHD_COOKIE_KIND, Context::process_connection_values, this);
}

string Http::Context::dumpJson() {
    json j;
    j["uri"] = uri_;
    j["method"] = method_;
    j["headers"] = headers_;
    j["cookies"] = cookies_;
    j["getdata"] = getdata_;
    j["postdata"] = postdata_;
    return j.dump();
}

int Http::Context::process_connection_values(void *cls, enum MHD_ValueKind kind, const char *key, const char *value) {
    Context *context = (Context *) cls;
    string str_key(key);
    string str_val("");

    // Check for empty arguments
    if (NULL != value) {
        str_val = value;
    }

    // Decide where the data goes
    switch (kind) {
        case MHD_HEADER_KIND :          context->headers_[str_key] = str_val; break;
        case MHD_GET_ARGUMENT_KIND :    context->getdata_[str_key] = str_val; break;
        case MHD_COOKIE_KIND :          context->cookies_[str_key] = str_val; break;
        case MHD_RESPONSE_HEADER_KIND:break;
        case MHD_POSTDATA_KIND:break;
        case MHD_FOOTER_KIND:break;
    }

    return MHD_YES;
}

void Http::Context::completed(void *cls, struct MHD_Connection *connection, void **con_cls,
                              enum MHD_RequestTerminationCode toe) {
    if (NULL == con_cls ) return;

    Context *context = (Context *) *con_cls;
    delete context;
}
