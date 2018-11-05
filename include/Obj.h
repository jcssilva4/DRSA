#ifndef OBJ_H
#define OBJ_H

#include "includes.h"

class Obj
{
    public:
        Obj(string, float*, int);
        virtual ~Obj();
        string get_Name();
        void update_GranulesOfKnowledge(vector<Obj*>, vector<int>);
        void update_PdominatingSet(Obj*);
        void update_PdominatedSet(Obj*);
        void show_PdominatingSet();
        vector<Obj*> get_PdominatingSet();
        int get_Class();

    protected:

    private:
        string name; // object's name
        int clss; // object's class
        vector<float> g; // criteria evaluation on this object
        vector<Obj*> PdominatingSet; // set of objects Obj' such that thisObj_g[i] <= Obj'_g[i] for all i
        vector<Obj*> PdominatedSet; // set of objects Obj' such that thisObj_g[i] >= Obj'_g[i] for all i
};

#endif // OBJ_H
