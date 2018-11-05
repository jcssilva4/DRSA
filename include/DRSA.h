#ifndef DRSA_H
#define DRSA_H

#include "Obj.h"

class DRSA
{
    public:
        DRSA(int, int, int*, int, float**);
        virtual ~DRSA();
        bool checkApproxMembership(int, bool, bool, Obj*);
        vector<Obj*> get_upClt(int); // compute upward union of classes s>=t
        vector<Obj*> get_downClt(int);
    protected:

    private:
        int nObj;
        int nCriteria;
        int nClasses;
        vector<int> prefDir; //criteria monotonic restrictions directions (preference direction - max=1,min=-1)
        vector<Obj*> Universe;
        // Universe Partitions
        map<int,vector<Obj*>> Clt;
        // approximations of unions of classes
        map<int,vector<Obj*>>PLaprx_Clt_up; // P-lower approximation of upward union of classes (Clt = {x | x belongs to Cls, s>=t})
        map<int,vector<Obj*>>PUaprx_Clt_up; // P-upper approximation of upward union of classes (Clt = {x | x could belong to Cls, s>=t})
        map<int,vector<Obj*>>PBndry_Clt_up; // boundary  (Clt = {x | x could belong to Cls, s<=t})
        map<int,vector<Obj*>>PLaprx_Clt_down; // P-lower approximation of downward union of classes (Clt = {x | x could belong to Cls, s<=t})
        map<int,vector<Obj*>>PUaprx_Clt_down; // P-upper approximation of downward union of classes (Clt = {x | x could belong to Cls, s<=t})
        map<int,vector<Obj*>>PBndry_Clt_down; // boundary (Clt = {x | x could belong to Cls, s<=t})
};

#endif // DRSA_H
