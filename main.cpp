/**
 * Demo file for the exercise on iterators
 *
 * @author Tal Zichlinsky
 * @since 2022-02
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "OrgChart.hpp"
using namespace ariel;

int main() {
    OrgChart organization;
    organization.add_root("CEO")
            .add_sub("CEO", "CTO")
            .add_sub("CEO", "CFO")
            .add_sub("CEO", "COO")
            .add_sub("CTO", "VP_SW")
            .add_sub("COO", "VP_BI");

    cout <<"The organization tree:\n"<< organization << endl; 
    /*
       CEO
       |--------|--------|
       CTO      CFO      COO
       |                 |
       VP_SW             VP_BI
 */

    cout<<"Level order: " << endl;
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it){
        cout << (*it) << " " ;
    } // prints: CEO CTO CFO COO VP_SW VP_BI


    cout<<endl<<endl<<"Reverse order: " << endl;
    for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it){
        cout << (*it) << " " ;
    } // prints: VP_SW VP_BI CTO CFO COO CEO


    cout<<endl<<endl<<"Pre order: " << endl;
    for (auto it=organization.begin_preorder(); it!=organization.end_preorder(); ++it) {
        cout << (*it) << " " ;
    }  // prints: CEO CTO VP_SW CFO COO VP_BI


    cout<<endl<<endl<<"element:organization - print Level order: " << endl;
    for (auto element : organization){
        cout << element << " " ;
    } // prints: CEO CTO CFO COO VP_SW VP_BI


    cout<<endl<<endl<< "demonstrate the arrow operator-> prints length of names of level order: " <<endl;
    // demonstrate the arrow operator:
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it){
        cout << it->size() << " " ;
    } // prints: 3 3 3 3 5 5

    cout << endl<<endl;

    OrgChart<double> organization_double;
    organization_double.add_root(1)
            .add_sub(1, 1.1)
            .add_sub(1, 1.2)
            .add_sub(1, 1.3)
            .add_sub(1.1, 1.11)
            .add_sub(1.2, 1.21);

    cout <<"The organization double tree:"<< endl << organization_double << endl<<endl<< "Level order: "<<endl;


    for (auto it = organization_double.begin_level_order(); it != organization_double.end_level_order(); ++it){
        cout << (*it) << " " ;
    } // prints: 1 1.1 1.2 1.3 1.11 1.21

    cout<<endl<<endl<<"Reverse order for organization double: "<<endl;
    for (auto it = organization_double.begin_reverse_order(); it != organization_double.reverse_order(); ++it){
        cout << (*it) << " " ;
    } // prints: 1.11 1.21 1.1 1.2 1.3 1

    cout<<endl<<endl<<"Pre order for organization double: "<<endl;
    for (auto it=organization_double.begin_preorder(); it!=organization_double.end_preorder(); ++it) {
        cout << (*it) << " " ;
    }  // prints: 1 1.1 1.11 1.2 1.21 1.3

    cout<<endl<<endl<<"element:organization - print Level for order organization double: "<<endl;
    for (auto element : organization_double){
        cout << element << " " ;
    } // prints: 1 1.1 1.2 1.3 1.11 1.21
    cout << endl;
}