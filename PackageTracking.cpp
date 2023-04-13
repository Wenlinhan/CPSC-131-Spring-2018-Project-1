//
//  PackageTracking.cpp
//  Project2
//
//  Created by Han, Wenlin on 2/13/18.
//  Copyright © 2018 Han, Wenlin. All rights reserved.
//

#include "PackageTracking.h"

PackageTracking::PackageTracking(const string& strnum){
    m_numUpdate = 0;                            // initially empty
    m_header = new ShippingStatus;              // create sentinels
    m_trailer = new ShippingStatus;
    m_header->m_setNext(m_trailer);             // have them point to each other
    m_trailer->m_setPrev(m_header);
    m_cur = m_header; //set iterator
    m_trackingnumber = strnum;
    
}
PackageTracking::~PackageTracking(){
    if (!m_isEmpty()) m_clear();     // remove all but sentinels
    delete m_header;                            // remove the sentinels
    delete m_trailer;
    
}
// add a new update before trailer end
int PackageTracking::m_addUpdate( const string& status, const string& location, const time_t& timeUpdated){
    ShippingStatus* ptr_newupdate = new ShippingStatus(status, location, timeUpdated, nullptr, nullptr);
    if(!ptr_newupdate) return -1;
    ptr_newupdate->m_setNext(m_trailer);
    ShippingStatus* ptr_pretrailer = m_trailer->m_getPrev();
    ptr_newupdate->m_setPrev(ptr_pretrailer);
    ptr_pretrailer->m_setNext(ptr_newupdate);
    m_trailer->m_setPrev(ptr_newupdate);
    m_numUpdate++;
    m_cur = ptr_newupdate;// move cur pointer
    
    return 1;
}
/*
int m_addUpdate(const ShippingStatus& newupdate)// add a new update before trailer end
{
    return 1;
}
 */

int PackageTracking::m_removeUpdate()// remove the update before trailer end
{
    ShippingStatus* ptr_pretrailer = m_trailer->m_getPrev();
    if((ptr_pretrailer == m_header)||!ptr_pretrailer)
        return -1;
    ShippingStatus* ptr_prepretrailer = ptr_pretrailer->m_getPrev();
    if(!ptr_prepretrailer) return -1;
    ptr_prepretrailer->m_setNext(m_trailer);
    m_trailer->m_setPrev(ptr_prepretrailer);
    m_numUpdate--;
    delete ptr_pretrailer;
    
    return 1;
}

int PackageTracking::m_moveBackward()//move iterator one step towards header
{
    ShippingStatus* ptr_curpre = m_cur->m_getPrev();
    if(ptr_curpre == m_header)
        return -1;
    m_cur = ptr_curpre;
    return 1;
}

int PackageTracking::m_moveForward()//move iterator one step towards trailer
{
    ShippingStatus* ptr_curnext = m_cur->m_getNext();
    if(ptr_curnext == m_trailer)
        return -1;
    m_cur = ptr_curnext;
    return 1;
}

string PackageTracking::m_getLocation( )//return the location of the current update
{
    if(!m_cur) return "N/A";
    return m_cur->m_getLocation();
}

time_t PackageTracking::m_getTime( )//return the time of the current update
{
    if(!m_cur) return 0;
    time_t tmp_tt = m_cur->m_getTime();
    return tmp_tt;
}

string PackageTracking::m_getStatus( )//return the status of the current update
{
    if(!m_cur)  return "N/A";
    return m_cur->m_getStatus();
}

int PackageTracking::m_getNumofUpdate() const // get the total numbers of shipping status updates
{
    return m_numUpdate;
}

int PackageTracking::m_printPreviousUpdates() //print all previous updates in the shipping chain when the package was shipped, all the way up to (but not including) the current update you are viewing (may not be the most recent update).
{

    if(m_isEmpty() || (m_cur->m_getPrev() == m_header))
    {
        cout<<"no previous updates"<<endl;
        return -1;
    }
    ShippingStatus* ptr_cur = m_cur;
    while(m_cur->m_getPrev()!=m_header)
    {
        m_moveBackward();
        cout<<m_getTime()<<": "<<m_getStatus()<<": "<<m_getLocation()<<endl;
        
    }
    m_cur = ptr_cur;// reset m_cur
    return 1;
}
int PackageTracking::m_printFollowingUpdates()//print all following updates including the current update you are viewing. From the current update you are viewing to the last update in the tracking chain.
{

    cout<<m_getTime()<<": "<<m_getStatus()<<": "<<m_getLocation()<<endl;
    if(m_isEmpty() ||(m_cur->m_getNext()==m_trailer))
    {
        cout<<"no following updates"<<endl;
        return -1;
    }
    ShippingStatus* ptr_cur = m_cur;
    while(m_cur->m_getNext()!=m_trailer)
    {
        m_moveForward();
        cout<<m_getTime()<<": "<<m_getStatus()<<": "<<m_getLocation()<<endl;
    }
    m_cur = ptr_cur;// reset m_cur
    return 1;
}

int PackageTracking::m_printFullTracking()//print all the updates in the tracking chain.
{
    cout<<"Tracking number: "<< m_getTrackingnumber()<<endl;
    if(m_isEmpty()){
        cout<<"no updates"<<endl;
        return -1;
    }
    ShippingStatus* ptr_cur = m_cur;
    while(m_cur!=m_header->m_getNext())// move m_cur to the first element
        m_moveBackward();
    
    while(m_cur!=m_trailer->m_getPrev())//iterate and print
    {
        cout<<m_getTime()<<": "<<m_getStatus()<<": "<<m_getLocation()<<endl;
        m_moveForward();
    }
    if(m_cur==m_trailer->m_getPrev())//the only data element or the last element
        cout<<m_getTime()<<": "<<m_getStatus()<<": "<<m_getLocation()<<endl;
    
    m_cur = ptr_cur;
    return 1;
}

bool PackageTracking::m_isEmpty() const//check empty
{
    if(m_header->m_getNext()==m_trailer)
        return true;
    return false;
}

void PackageTracking::m_clear()//remove all but sentinels
{
    while (!m_isEmpty())
        m_removeUpdate();
}

string PackageTracking::m_getTrackingnumber(){
    return m_trackingnumber;
}

int PackageTracking::m_viewUpdate(const time_t& timeUpdated)//view an update.
{
    if(m_isEmpty()) return -1;
    m_cur = m_header->m_getNext();
    while((m_cur->m_getTime()!=timeUpdated)&&(m_cur->m_getNext()!=m_trailer))
        m_moveForward();
    return 1;
}
//read the full tracking chain from a file and follow the commands as specified in the file
int PackageTracking::m_readTrackingFile(string fileName) {

    ifstream infile;
    infile.open(fileName);

    while (infile)
    {
        string tmp_strline;
        if (!getline( infile, tmp_strline )) break;
        
        //cout<<tmp_strline<<endl;
        if(tmp_strline == "new"){
            if (!getline( infile, tmp_strline )) break;//get next line
            istringstream tmp_str( tmp_strline );
            string tmp_loc, tmp_sta,tmp_strtime;
            time_t tmp_tt;
            if (!getline( tmp_str, tmp_sta, ';' )) break;
            if (!getline( tmp_str, tmp_loc, ';' )) break;
            if (!getline( tmp_str, tmp_strtime, ';' )) break;
            stringstream geek(tmp_strtime);
            int i_time = 0;
            geek >> i_time;
            tmp_tt = (time_t)i_time;
            //cout<<tmp_loc<<";"<<tmp_sta<<";"<<tmp_strtime<<endl;
            m_addUpdate(tmp_sta,tmp_loc,tmp_tt);
            
        }else if(tmp_strline == "back") {
            m_moveBackward();
        } else if(tmp_strline == "forward") {
            m_moveForward();
        } else {
            return -2;
        }
    }
    if (!infile.eof())
    {
        return -1;
    }
    return 1;
}
