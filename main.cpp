#include "DRSA.h"

int main()
{
    cout << "\nreading data table...";
    DataTable data("datafiles/datatable1.txt"); //get data table
    cout << "\nstart DRSA..." << endl;
    DRSA RS(data.get_nObj(), data.get_nCriteria(), data.get_prefDir(), data.get_nClasses(), data.get_f());
    cout << endl;
    return 0;
}
