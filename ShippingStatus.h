//
//  ShippingStatus.hpp
//  Project2
//
//  Created by Han, Wenlin on 2/13/18.
//  Copyright © 2018 Han, Wenlin. All rights reserved.
//

#ifndef ShippingStatus_h
#define ShippingStatus_h

#pragma once

#include <stdio.h>
#include <string>
using namespace std;

class ShippingStatus {
public:
    ShippingStatus();
    ShippingStatus(const string& status, const string& location, const time_t& timeUpdated,  ShippingStatus* prev,  ShippingStatus* next);
    ~ShippingStatus();
    string m_getStatus();
    string m_getLocation();
    time_t m_getTime();
    ShippingStatus* m_getPrev();
    ShippingStatus* m_getNext();

    int m_setStatus(const string& status);
    int m_setLocation(const string& location);
    int m_setTime(const time_t& timeUpdated);
    int m_setPrev( ShippingStatus* prev);
    int m_setNext( ShippingStatus* next);
    
private:
    string m_strStatus;
    string m_strLocation;
    time_t m_ttTime;
    ShippingStatus *m_prev, *m_next;
};


#endif /* ShippingStatus_h */
