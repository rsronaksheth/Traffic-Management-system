#ifndef TRAFFIC_H
#define TRAFFIC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxlen 100
#define VIOLATION_COUNT 1
#define TOTAL_REVENUE 2

//surcharge of 10%

typedef enum {
    illegalpark,
    overspeed,
    redlightjump,
    helmetorbelt
}Viotype;

typedef struct ViolationData_tag{
    Viotype vt;
    int frequency;
}ViolationData;

//0 = illegalpark fine 300rs
//1=overspeed  fine 500rs
//2=redlightjump  1000rs
//3=helemtorbelt   2000rs

typedef enum{online,cash}Mode;  //0- online 1-offline

typedef struct Date_tag{
    int day;
    int month;
    int year;
}Date;

typedef struct Time_tag{
    int sec;
    int min;
    int hour;
}Time;

typedef enum { false, true } bool;

typedef struct Vehicle_tag{
    char regNo[maxlen];
    char name[maxlen];
    long long int contactNo;
    char address[maxlen];
    float totalFines;
    float paidFines;
    float pendingAmount;
    int numViolations;

    int height;
    struct Vehicle_tag*left;
    struct Vehicle_tag*right;
}Vehicle;

typedef struct VehicleData_tag{
    Vehicle *v;
    int unpaidCount;
}VehicleData; //for sort function later

typedef struct VehiclePendingData_tag{
    Vehicle *v;
    float pendingAmount;
}VehiclePendingData;

typedef struct Violation_tag{
    char vioId[maxlen];
    char regNo[maxlen];
    Viotype vt;
    char locId[maxlen];
    Date d;
    Time t;
    bool isPaid;
    float amount;

    int height;
    struct Violation_tag*left;
    struct Violation_tag*right;
}Violation;

typedef struct ViolationRepeatData_tag{
    Viotype vt;
    int totalCount;
    int repeatCount;
    float fraction;
}ViolationRepeatData;

typedef struct Location_tag{
    char locId[maxlen];
    char locName[maxlen];

    int height;
    struct Location_tag*left;
    struct Location_tag*right;
}Location;

typedef struct LocationData_tag{
    Location *loc;
    int violationCount;
    float totalRevenue;
}LocationData;

typedef struct Node_tag{
    char transactionId[maxlen];
    Violation *v;
    float amountpaid;
    Mode payMode;
    Date payDate;
    struct Node_tag*next;
}Node;

typedef struct Transaction_tag{
    Node*top;
}Transactions;

int height(Vehicle *n);
int getMax(int a, int b);
int getBalance(Vehicle *n);
Vehicle* RotateRight(Vehicle *root);
Vehicle* RotateLeft(Vehicle *root);
void InitialiseTranasaction(Transactions *t);
void takedate(Date *date);
void taketime(Violation *nptr);
void uppercase(char *str);
int correctregno(char *str);
Vehicle* searchVeh(char *regNo,Vehicle *veh);
void takeinfo(Vehicle*nptr,Vehicle*v);
Vehicle* insertvehicle(Vehicle *v, Vehicle *nptr);
Vehicle* registerVehicle(Vehicle *v);
Location* searchLoc(char *locId,Location *l);
void takeViotype(Viotype *vt); 
float calcfineandupdateowner(Vehicle *veh,Viotype vt);
Violation* insertViolation(Violation *vio, Violation *nptr);
void generatevioId(char *id, int *viocount);
Violation* reportViolation(Violation*vio,int *viocount,Location*l,Vehicle*veh);
Violation* searchViolation(char *vioId,Violation *vio);
void generateTransactionId(char *id,int *transactionCount);
void ownerViolations(Vehicle *v, Violation *vio, Location *loc);
void locationViolations(Vehicle *v, Violation *vio, Location *loc);
void sortLocationsByViolationCount(Location *loc, Violation *vio);
void sortLocationsByRevenue(Location *loc, Violation *vio);
void sortViolationTypes(Violation *vio);
void sortViolationTypesByRepeatOffenders(Vehicle *v, Violation *vio);
void displayVehiclesByThreshold(Vehicle *v);
void displayPendingViolations(Vehicle *v, Violation *vio);
void displayPaymentHistory(Transactions *t);
void loadVehicles(Vehicle **v, int *check);
void loadViolations(Violation **v, int *check);
void loadLocations(Location **l, int *check);
void loadTransactions(Transactions **tr, Violation *vio, int *check);
void overwriteVehicles(Vehicle *v, int *check);
void overwriteViolations(Violation *vio, int *check);
void overwriteLocations(Location *loc, int *check);
void overwriteTransactions(Transactions *t, int *check);
void printLocations(Location *loc);
void displayRangeViolationsChronological(Violation *root, char *V1, char *V2);
Transactions* payfine(Transactions *t, Vehicle *v, Violation *vio, int *transactionCount);
void sortVehiclesByUnpaidCount(Vehicle *v, Violation *vio);
void sortVehiclesByPendingAmount(Vehicle *v);
Location* insertLocation(Location *l, Location *nptr);
Vehicle* insertVehicle(Vehicle *v, Vehicle *nptr);



#endif