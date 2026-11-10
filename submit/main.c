#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct.h"

int main(){
    Vehicle *v=NULL;  //main storage of vehicles
    Violation *vio=NULL; //main for all violations
    Location *loc=NULL; //main for all Locations
    Transactions *t=(Transactions*)malloc(sizeof(Transactions));
    t->top=NULL;
    int check = 0;
    loadVehicles(&v, &check);
    loadViolations(&vio, &check);
    loadLocations(&loc, &check);
    loadTransactions(&t, vio, &check);
    if(check == 1){
        printf("Error loading vehicle data.\n");
        return 0;
    }
    printf("All files loaded successfully.\n");
    printLocations(loc);
    int exit=0,choice;
    int viocount=10; //for now let it be
    int transactionCount=10; //for now ;et it be
    while(!exit){
        printf("Enter Choice :\n");
        printf("Enter 1 for Exit\n");
        printf("Enter 2 for Registering new Vehicle\n");
        printf("Enter 3 for Reporting an violation :\n");
        printf("Enter 4 for Paying for an violation :\n");
        printf("Enter 5 to print all vehicles registered for an owner along with violations :\n");
        printf("Enter 6 for printing all violations occoured at given Location along with details:\n");
        printf("Enter 7 display all vehicles in desending order of no. of unpaid violations :\n");
        printf("Enter 8 to display all locations in desending order of no. of violations occoured there :\n");
        printf("Enter 9 to display all locations in desending order of total amoubt of fine generated there :\n");
        printf("Enter 10 to display all violation types in desending order based on how frequently they occour:\n");
        printf("Enter 11 to display what fraction of those violations were committed by repeat offenders ,and display violation types ranked by this proportion :\n");
        printf("Enter 12 to display all vehicles whose violation count is greater than or equal to an threshold, along with the owner's details:\n");
        printf("Enter 13 to display all of Entered Vehicle reg.no's pending (unpaid) violations along with their details\n");
        printf("Enter 14 to  display all vehicles in descending order based on their pending fine amount:\n");
        printf("Enter 15 to Display the complete payment history in reverse chronological order, showing the transaction ID, violation paid, amount, and mode of payment:\n");
        printf("Enter 16 to Display Violations by ID Range (Chronological)\n");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                exit=1;
                break;
            case 2:
                v=registerVehicle(v);
                break;
            case 3:
                vio=reportViolation(vio,&viocount,loc,v);
                break;
            case 4:
                t=payfine(t,v,vio,&transactionCount);
                break;
            case 5:
                ownerViolations(v,vio,loc);
                break;
            case 6:
                locationViolations(v,vio,loc);
                break;
            case 7:
                sortVehiclesByUnpaidCount(v,vio);
                break;
            case 8:
                sortLocationsByViolationCount(loc,vio);
                break;
            case 9:
                sortLocationsByRevenue(loc,vio);
                break;
            case 10:
                sortViolationTypes(vio);
                break;
            case 11:
                sortViolationTypesByRepeatOffenders(v,vio);
                break;
            case 12:
                displayVehiclesByThreshold(v);
                break;
            case 13:
                displayPendingViolations(v,vio);
                break;
            case 14:
                sortVehiclesByPendingAmount(v);
                break;
            case 15:
                displayPaymentHistory(t);
                break;
            case 16: {
                char V1[maxlen], V2[maxlen];
                printf("Enter starting Violation ID (V1): ");
                scanf("%s", V1);
                uppercase(V1);
                printf("Enter ending Violation ID (V2): ");
                scanf("%s", V2);
                uppercase(V2);
                displayRangeViolationsChronological(vio,V1,V2);
                break;
            }
        }
    }
    overwriteVehicles(v, &check);
    overwriteViolations(vio, &check);
    overwriteLocations(loc, &check);
    overwriteTransactions(t, &check);
    if(check == 1){
        printf("Error overwriting file.\n");
        return 0;
    }
    return 0;
}