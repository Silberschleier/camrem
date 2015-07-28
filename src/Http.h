//
// Created by Christopher Schmidt on 27.07.15.
//

#ifndef CAMREM_HTTP_H
#define CAMREM_HTTP_H
#include "Helpers.h"


class Http {
private:
    Http(void);
    ~Http(void);

public:
    /*
     * The instance of Http is defined and created in here.
     * @return The instance of Http
     */
    static Http * getInstance();
};


#endif //CAMREM_HTTP_H
