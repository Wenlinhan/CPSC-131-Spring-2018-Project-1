//
//  PackageTracking.h
//  Project2
//
//  Created by Han, Wenlin on 2/13/18.
//  Copyright © 2018 Han, Wenlin. All rights reserved.
//

#ifndef PackageTracking_h
#define PackageTracking_h

#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <sstream>
#include <stdexcept>
#include "ShippingStatus.h"
using namespace std;

class PackageTracking {
public:
    PackageTracking(const string& strnum);
    ~PackageTracking();
    
    int m_addUpdate( const string& status, const string& location, const time_t& timeUpdated);// add a new update before trailer end
    //int m_addUpdate(const ShippingStatus& newupdate);// add a new update before trailer end
    int m_removeUpdate();// remove the update before trailer end
    
    int m_moveBackward();//move iterator one step towards header
    int m_moveForward();//move iterator one step towards trailer

    string m_getLocation( );//return the location of the current update
    time_t m_getTime( );//return the time of the current update
    string m_getStatus( );//return the status of the current update
    int m_getNumofUpdate() const; // get the total numbers of shipping status updates
    
    int m_viewUpdate(const time_t& timeUpdated);//view an update.
    
    int m_printPreviousUpdates();  //print all previous updates in the shipping chain when the package was shipped, all the way up to (but not including) the current update you are viewing (may not be the most recent update).
    int m_printFollowingUpdates();//print all following updates including the current update you are viewing. From the current update you are viewing to the last update in the tracking chain.
    
    int m_printFullTracking();//print all the status updates in the tracking chain.
    bool m_isEmpty() const;//check empty
    void m_clear();//remove all but sentinels

    string m_getTrackingnumber();
    //read the full tracking chain from a file and follow the commands as specified in the file
    int m_readTrackingFile(string fileName);
    
    
private:
    ShippingStatus *m_header, *m_trailer, *m_cur;//header, trailer, iterator
    int m_numUpdate;//number of updates
    string m_trackingnumber;//package tracking number
};

#endif /* PackageTracking_h */
