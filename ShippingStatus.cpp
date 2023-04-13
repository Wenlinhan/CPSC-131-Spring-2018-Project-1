//
//  ShippingStatus.cpp
//  Project2
//
//  Created by Han, Wenlin on 2/13/18.
//  Copyright © 2018 Han, Wenlin. All rights reserved.
//

#include "ShippingStatus.h"


ShippingStatus::ShippingStatus() {
    m_strStatus = "";
    m_strLocation = "";
    m_ttTime = 0;
    m_prev = nullptr;
    m_next = nullptr;
}

ShippingStatus::~ShippingStatus()
{
    
}

ShippingStatus::ShippingStatus(const string& status, const string& location, const time_t& timeUpdated, ShippingStatus* prev,  ShippingStatus* next) {
    m_strStatus = status;
    m_strLocation = location;
    m_ttTime = timeUpdated;
    m_prev = prev;
    m_next = next;
}

string ShippingStatus::m_getStatus(){
    return m_strStatus;
}

string ShippingStatus::m_getLocation(){
    return m_strLocation;
}


time_t ShippingStatus::m_getTime() {
    return m_ttTime;
}

ShippingStatus* ShippingStatus::m_getPrev(){
    return m_prev;
}

ShippingStatus* ShippingStatus::m_getNext(){
    return m_next;
}

int ShippingStatus::m_setStatus(const string& status){
    m_strStatus = status;
    return 1;
}
int ShippingStatus::m_setLocation(const string& location){
    m_strLocation = location;
    return 1;
}
int ShippingStatus::m_setTime(const time_t& timeUpdated){
    m_ttTime = timeUpdated;
    return 1;
}
int ShippingStatus::m_setPrev(ShippingStatus* prev){
    m_prev = prev;
    return 1;
}
int ShippingStatus::m_setNext(ShippingStatus* next){
    m_next = next;
    return 1;
}
