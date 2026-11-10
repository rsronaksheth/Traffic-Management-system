#include <stdio.h>
#include <stdlib.h>
#include "struct.h"


int height(Vehicle *n){
    int retval;
    if(n==NULL){
        retval= 0;
    }else{
        retval= n->height;
    }
    return retval;
}

int getMax(int a, int b) {
    int retval;
    if (a > b) {
        retval= a;
    }else{
        retval=b;
    }
    return retval;
}

int getBalance(Vehicle *n){
    int retval;
    if (n == NULL) {
        retval= 0;
    }else{
        retval=height(n->left) - height(n->right);
    }
    return retval;
}

Vehicle* RotateRight(Vehicle *root) {
    Vehicle *p = root;
    Vehicle *q = NULL;
    if (p == NULL || p->left == NULL) {
        q = root;
    } else {
        q = p->left;
        p->left = q->right;
        q->right = p;
        p->height = getMax(height(p->left), height(p->right)) + 1;
        q->height = getMax(height(q->left), height(q->right)) + 1;
    }
    return q;
}

Vehicle* RotateLeft(Vehicle *root) {
    Vehicle *p = root;
    Vehicle *q = NULL;
    if (p == NULL || p->right == NULL) {
        q = root;
    } else {
        q = p->right;
        p->right = q->left;
        q->left = p;
        p->height = getMax(height(p->left), height(p->right)) + 1;
        q->height = getMax(height(q->left), height(q->right)) + 1;
    }   
    return q;
}

// --- Violation AVL Helpers ---
int violationHeight(Violation *n) {
    if (n == NULL) return 0;
    return n->height;
}

int getViolationBalance(Violation *n) {
    if (n == NULL) return 0;
    return violationHeight(n->left) - violationHeight(n->right);
}

Violation* rotateRightViolation(Violation *root) {
    Violation *p = root;
    Violation *q = p->left;
    p->left = q->right;
    q->right = p;
    p->height = getMax(violationHeight(p->left), violationHeight(p->right)) + 1;
    q->height = getMax(violationHeight(q->left), violationHeight(q->right)) + 1;
    return q;
}

Violation* rotateLeftViolation(Violation *root) {
    Violation *p = root;
    Violation *q = p->right;
    p->right = q->left;
    q->left = p;
    p->height = getMax(violationHeight(p->left), violationHeight(p->right)) + 1;
    q->height = getMax(violationHeight(q->left), violationHeight(q->right)) + 1;
    return q;
}

// --- Location AVL Helpers ---
int locationHeight(Location *n) {
    if (n == NULL) return 0;
    return n->height;
}

int getLocationBalance(Location *n) {
    if (n == NULL) return 0;
    return locationHeight(n->left) - locationHeight(n->right);
}

Location* rotateRightLocation(Location *root) {
    Location *p = root;
    Location *q = p->left;
    p->left = q->right;
    q->right = p;
    p->height = getMax(locationHeight(p->left), locationHeight(p->right)) + 1;
    q->height = getMax(locationHeight(q->left), locationHeight(q->right)) + 1;
    return q;
}

Location* rotateLeftLocation(Location *root) {
    Location *p = root;
    Location *q = p->right;
    p->right = q->left;
    q->left = p;
    p->height = getMax(locationHeight(p->left), locationHeight(p->right)) + 1;
    q->height = getMax(locationHeight(q->left), locationHeight(q->right)) + 1;
    return q;
}

void InitialiseTranasaction(Transactions *t){
    t->top=NULL;
    return; 
}
void takedate(Date *date){
    int y,m,d;
    int valid=0;
    while(valid==0){
        printf("Enter year:\n");
        scanf("%d",&y);
        printf("Enter Month:\n");
        scanf("%d",&m);
        printf("Enter Day:\n");
        scanf("%d",&d);
        valid=1;
        if(m<1 || m>12){
            valid=0;
        }else if(d<1){
            valid=0;
        }else if(m==2){
            if((y%400==0) || (y%4==0 && y%100!=0)){
                if(d>29){
                    valid=0;
                }
            }else{
                if(d>28){
                    valid=0;
                }
            }
        }else if(m==4 || m==6 || m==9 || m==11){
            if(d>30){
                valid=0;
            }
        }else if(d>31){
            valid=0;
        }
        if(valid==0){
            printf("Invalid date. Enter again.\n");
        }
    }
    date->day=d;
    date->month=m;
    date->year=y;
}

void taketime(Violation *nptr){
    int h,m,s;
    int valid=0;
    while(valid==0){
        printf("Enter hour (0-23):\n");
        scanf("%d",&h);
        printf("Enter minute (0-59):\n");
        scanf("%d",&m);
        printf("Enter second (0-59):\n");
        scanf("%d",&s);
        valid=1;
        if(h<0 || h>23){
            valid=0;
        }else if(m<0 || m>59){
            valid=0;
        }else if(s<0 || s>59){
            valid=0;
        }
        if(valid==0){
            printf("Invalid time. Enter again.\n");
        }
    }
    nptr->t.hour=h;
    nptr->t.min=m;
    nptr->t.sec=s;
    return;
}

void uppercase(char *str){
    int i=0;
    while(str[i]!='\0'){
        if(str[i]>='a' && str[i]<='z'){
            str[i]=str[i]-'a'+'A';
        }
        i++;
    }
}

int correctregno(char *str){
    //as our format of 10 characters MH04AB1234
    int valid=1;
    if(strlen(str)!=10){
        valid=0;
    }else{
        for(int i=0;i<2;i++){
            if(str[i]<'A'|| str[i]>'Z'){
                valid=0;
            }
        }
        for(int i=2;i<4;i++){
            if(str[i]<'0'|| str[i]>'9'){
                valid=0;
            }
        }
        for(int i=4;i<6;i++){
            if(str[i]<'A'|| str[i]>'Z'){
                valid=0;
            }
        }
        for(int i=6;i<10;i++){
            if(str[i]<'0'|| str[i]>'9'){
                valid=0;
            }
        }
    }
    return valid;
}

Vehicle* searchVeh(char *regNo, Vehicle *veh) {
    Vehicle *p = veh;
    Vehicle *result = NULL;
    while (p != NULL) {
        int cmp = strcmp(regNo, p->regNo);
        if (cmp == 0) {
            result = p;
            p = NULL;
        } else if (cmp < 0) {
            p = p->left;
        } else {
            p = p->right;
        }
    }   
    return result;
}

void takeinfo(Vehicle*nptr,Vehicle *v){
    int valid=0;
    Vehicle *chk;
    do{
        printf("Enter Registration Number (e.g. MH31AB1234):\n");
        scanf("%s",nptr->regNo);
        uppercase(nptr->regNo);
        valid=correctregno(nptr->regNo);
        chk=searchVeh(nptr->regNo,v);
        if(valid==0){
            printf("Invalid Registration Number. Enter again.\n");
        }
        if(chk!=NULL){
            printf("Already Exists !\n");
            valid=0;
        }
    }while(valid==0);
    printf("Enter Owner Name:\n");
    scanf("%s",nptr->name);
    uppercase(nptr->name);
    printf("Enter Contact Number:\n");
    scanf("%lld",&nptr->contactNo);
    printf("Enter Address:\n");
    scanf("%s",nptr->address);
    nptr->totalFines=0;
    nptr->paidFines=0;
    nptr->pendingAmount=0;
    nptr->numViolations=0;
    return;
}

Vehicle* insertvehicle(Vehicle *v, Vehicle *nptr) {
    Vehicle *result = v;
    Vehicle *p = v;
    if (p == NULL) {
        nptr->left = NULL;
        nptr->right = NULL;
        nptr->height = 1;
        result = nptr;
    } else {
        int cmp = strcmp(nptr->regNo, p->regNo);
        if (cmp < 0) {
            p->left = insertvehicle(p->left, nptr);
            result = p;
        } else if (cmp > 0) {
            p->right = insertvehicle(p->right, nptr);
            result = p;
        } else {
            printf("Vehicle with this Registration Number already exists.\n");
            free(nptr);
            result = p;
        }
        if (cmp != 0) {
            p->height = getMax(height(p->left), height(p->right)) + 1;
            int balance = getBalance(p);
            if (balance > 1 && strcmp(nptr->regNo, p->left->regNo) < 0) {
                result = RotateRight(p);
            }
            else if (balance < -1 && strcmp(nptr->regNo, p->right->regNo) > 0) {
                result = RotateLeft(p);
            }
            else if (balance > 1 && strcmp(nptr->regNo, p->left->regNo) > 0) {
                p->left = RotateLeft(p->left);
                result = RotateRight(p);
            }
            else if (balance < -1 && strcmp(nptr->regNo, p->right->regNo) < 0) {
                p->right = RotateRight(p->right);
                result = RotateLeft(p);
            } else {
                result = p;
            }
        }
    }
    return result;
}

Vehicle* registerVehicle(Vehicle *v) {
    Vehicle *nptr = (Vehicle*)malloc(sizeof(Vehicle));
    if (nptr == NULL) {
        printf("Memory allocation failed.\n");
        return v;
    }
    takeinfo(nptr, v);
    v = insertvehicle(v, nptr);
    return v;
}

Location* searchLoc(char *locId, Location *l) {
    Location *p = l;
    Location *result = NULL;
    while (p != NULL) {
        int cmp = strcmp(locId, p->locId);
        if (cmp == 0) {
            result = p;
            p = NULL; // Terminate loop once found
        } else if (cmp < 0) {
            p = p->left;
        } else {
            p = p->right;
        }
    }   
    return result;
}

void takeViotype(Viotype *vt){
    int choice;
    int valid=0;
    while(valid==0){
        printf("Enter Violation Type:\n");
        printf("0 - Illegal Parking\n");
        printf("1 - Overspeeding\n");
        printf("2 - Red Light Jump\n");
        printf("3 - Helmet/Seatbelt\n");
        scanf("%d",&choice);
        if(choice>=0 && choice<=3){
            valid=1;
        }else{
            printf("Invalid Violation Type. Enter again.\n");
        }
    }
    *vt=(Viotype)choice;
}

float calcfineandupdateowner(Vehicle *veh,Viotype vt){
    float fine=0;
    if(vt==illegalpark){
        fine=300;
    }else if(vt==overspeed){
        fine=500;
    }else if(vt==redlightjump){
        fine=1000;
    }else{
        fine=2000;
    }
    if(veh->numViolations>2){
        fine=fine+(fine*0.10);
    }
    veh->totalFines=veh->totalFines+fine;
    veh->pendingAmount=veh->pendingAmount+fine;
    veh->numViolations++;
    return fine;
}

Violation* insertViolation(Violation *vio, Violation *nptr){
    Violation *result = vio;
    Violation *p = vio;
    if (p == NULL) {
        nptr->left = NULL;
        nptr->right = NULL;
        nptr->height = 1;
        result = nptr;
    } else {
        int cmp = strcmp(nptr->vioId, p->vioId);        
        if (cmp < 0) {
            p->left = insertViolation(p->left, nptr);
            result = p;
        } else if (cmp > 0) {
            p->right = insertViolation(p->right, nptr);
            result = p;
        } else {
            printf("Violation with this ID already exists.\n");
            free(nptr);
            result = p; 
        }
        if (cmp != 0) {
            p->height = getMax(violationHeight(p->left), violationHeight(p->right)) + 1;
            int balance = getViolationBalance(p);
            if (balance > 1 && getViolationBalance(p->left) >= 0) {
                result = rotateRightViolation(p);
            }
            else if (balance < -1 && getViolationBalance(p->right) <= 0) {
                result = rotateLeftViolation(p);
            }
            else if (balance > 1 && getViolationBalance(p->left) < 0) {
                p->left = rotateLeftViolation(p->left);
                result = rotateRightViolation(p);
            }
            else if (balance < -1 && getViolationBalance(p->right) > 0) {
                p->right = rotateRightViolation(p->right);
                result = rotateLeftViolation(p);
            } else {
                result = p;
            }
        }
    }
    return result;
}

void generatevioId(char *id, int *viocount) {
    int n;
    (*viocount)++;
    n = *viocount;
    id[0] = 'V';
    id[5] = '\0';
    id[4] = (n % 10) + '0';
    n = n / 10;
    id[3] = (n % 10) + '0';
    n = n / 10;
    id[2] = (n % 10) + '0';
    n = n / 10;
    id[1] = (n % 10) + '0';
    return;
}

Violation* reportViolation(Violation*vio,int *viocount,Location*l,Vehicle*veh){
    Violation*nptr=(Violation*)malloc(sizeof(Violation));
    char vId[maxlen];
    generatevioId(vId,viocount);
    strcpy(nptr->vioId,vId);
    char vehId[maxlen];
    char lId[maxlen];
    int valid=0;
    Vehicle *chk;
    while(valid==0){
        printf("Enter Reg no. of vehicle :\n");
        scanf("%s",vehId);
        uppercase(vehId);
        chk=searchVeh(vehId,veh);
        if(chk==NULL){
            valid=0;
            printf("Entered Id is wrong!!\n");
        }else{
            valid=1;
        }
    }
    strcpy(nptr->regNo,vehId);
    valid=0;
    takeViotype(&nptr->vt);
    while(valid==0){
        printf("Enter Location Id");
        scanf("%s",lId);
        uppercase(lId);
        Location* check=searchLoc(lId,l);
        if(check==NULL){
            valid=0;
            printf("Wrong Location Id:\n");
        }else{
            valid=1;
        }
    }
    strcpy(nptr->locId,lId);
    takedate(&nptr->d);
    taketime(nptr);
    nptr->isPaid=false;
    nptr->amount=calcfineandupdateowner(chk,nptr->vt);
    vio=insertViolation(vio,nptr);
    printf("Violation reported successfully. Violation ID: %s\n",nptr->vioId);
    return vio;
}

Violation* searchViolation(char *vioId, Violation *vio) {
    Violation *p = vio;
    Violation *result = NULL;
    while (p != NULL) {
        int cmp = strcmp(vioId, p->vioId);
        if (cmp == 0) {
            result = p;
            p = NULL;
        } else if (cmp < 0) {
            p = p->left;
        } else {
            p = p->right;
        }
    }
    return result;
}

void generateTransactionId(char *id,int *transactionCount){
    int n;
    (*transactionCount)++;
    n=*transactionCount;
    id[0]='T';
    id[5]='\0';
    id[4]=(n%10)+'0';
    n=n/10;
    id[3]=(n%10)+'0';
    n=n/10;
    id[2]=(n%10)+'0';
    n=n/10;
    id[1]=(n%10)+'0';
    return;
}

Transactions* payfine(Transactions*t,Vehicle*v,Violation*vio,int *transactionCount){
    char vioId[maxlen];
    Violation*checkvio=NULL;
    Vehicle*veh=NULL;
    Node*nptr=NULL;
    int valid=0;
    int choice;
    while(valid==0){
        printf("Enter Violation ID:\n");
        scanf("%s",vioId);
        uppercase(vioId);
        checkvio=searchViolation(vioId,vio);   
        if(checkvio==NULL){
            printf("Wrong Violation ID. Enter again.\n");
        }else if(checkvio->isPaid==true){
            printf("This violation is already paid.\n");
        }else{
            valid=1;
        }
    }
    veh=searchVeh(checkvio->regNo,v);
    printf("Fine Amount: %f\n",checkvio->amount);
    valid=0;
    while(valid==0){
        printf("Enter Payment Mode:\n");
        printf("0 - Online\n");
        printf("1 - Cash\n");
        scanf("%d",&choice);
        if(choice==0 || choice==1){
            valid=1;
        }else{
            printf("Invalid Payment Mode. Enter again.\n");
        }
    }
    nptr=(Node*)malloc(sizeof(Node));
    generateTransactionId(nptr->transactionId,transactionCount);
    nptr->v=checkvio;
    nptr->amountpaid=checkvio->amount;
    nptr->payMode=(Mode)choice; //or just if and accourdingly update
    printf("Enter Payment Date:\n");
    takedate(&nptr->payDate);
    checkvio->isPaid=true;
    veh->paidFines=veh->paidFines+checkvio->amount;
    veh->pendingAmount=veh->pendingAmount-checkvio->amount;
    if(t==NULL){ //inserting transaction at start (for ease)
        t=(Transactions*)malloc(sizeof(Transactions));
        InitialiseTranasaction(t);
    }
    nptr->next=t->top;
    t->top=nptr;
    printf("Payment successful. Transaction ID: %s\n",nptr->transactionId);
    return t;
}

void printVehicleViolations(Violation *p, char *targetRegNo, Location *loc, int *violationFound) {
    if (p != NULL) {
        printVehicleViolations(p->left, targetRegNo, loc, violationFound);
        if (strcmp(p->regNo, targetRegNo) == 0) {
            *violationFound = 1;
            printf("Violation ID: %s\n", p->vioId);
            if (p->vt == illegalpark) {
                printf("Type: Illegal Parking\n");
            } else if (p->vt == overspeed) {
                printf("Type: Overspeeding\n");
            } else if (p->vt == redlightjump) {
                printf("Type: Red Light Jump\n");
            } else {
                printf("Type: Helmet/Seatbelt\n");
            }
            Location *lcurr = searchLoc(p->locId, loc);
            if (lcurr != NULL) {
                printf("Location: %s\n", lcurr->locName);
            } else {
                printf("Location: Unknown\n");
            }   
            printf("Date: %d/%d/%d\n", p->d.day, p->d.month, p->d.year);
            printf("Fine Amount: %f\n", p->amount);
            if (p->isPaid == true) {
                printf("Payment Status: Paid\n");
            } else {
                printf("Payment Status: Pending\n");
            }
            printf("\n");
        }        
        printVehicleViolations(p->right, targetRegNo, loc, violationFound);
    }
}

void printOwnerVehicles(Vehicle *p, char *ownerName, Violation *vio, Location *loc, int *found) {
    if (p != NULL) {
        printOwnerVehicles(p->left, ownerName, vio, loc, found);
        if (strcmp(p->name, ownerName) == 0) {
            *found = 1;
            printf("\nVehicle Registration Number: %s\n", p->regNo);
            int violationFound = 0;
            printVehicleViolations(vio, p->regNo, loc, &violationFound);   
            if (violationFound == 0) {
                printf("No violations for this vehicle.\n");
            }
        }       
        printOwnerVehicles(p->right, ownerName, vio, loc, found);
    }
}

void ownerViolations(Vehicle *v, Violation *vio, Location *loc) {
    char ownerName[maxlen];
    int found = 0;
    printf("Enter Owner Name:\n");
    scanf("%s", ownerName);
    uppercase(ownerName);
    printOwnerVehicles(v, ownerName, vio, loc, &found);
    if (found == 0) {
        printf("No vehicle registered under this owner name.\n");
    }
    return;
}

void printLocationViolations(Violation *p, char *targetLocId, Vehicle *v, int *found) {
    if (p != NULL) {
        printLocationViolations(p->left, targetLocId, v, found);
        if (strcmp(p->locId, targetLocId) == 0) {
            *found = 1;
            Vehicle *veh = searchVeh(p->regNo, v);
            printf("\nViolation ID: %s\n", p->vioId);
            if (p->vt == illegalpark) {
                printf("Type: Illegal Parking\n");
            } else if (p->vt == overspeed) {
                printf("Type: Overspeeding\n");
            } else if (p->vt == redlightjump) {
                printf("Type: Red Light Jump\n");
            } else {
                printf("Type: Helmet/Seatbelt\n");
            }
            if (veh != NULL) {
                printf("Owner Name: %s\n", veh->name);
                printf("Contact Number: %lld\n", veh->contactNo);
            } else {
                printf("Owner Name: Unknown\n");
                printf("Contact Number: Unknown\n");
            }
        }
        printLocationViolations(p->right, targetLocId, v, found);
    }
}

void locationViolations(Vehicle *v, Violation *vio, Location *loc) {
    char locId[maxlen];
    Location *checkloc;
    int valid = 0, found = 0;
    while (valid == 0) {
        printf("Enter Location ID:\n");
        scanf("%s", locId);
        uppercase(locId);
        checkloc = searchLoc(locId, loc);
        if (checkloc == NULL) {
            printf("Wrong Location ID. Enter again.\n");
        } else {
            valid = 1;
        }
    }
    printLocationViolations(vio, locId, v, &found);   
    if (found == 0) {
        printf("No violations occurred at this location.\n");
    }
    return;
}

void InsertHeap(VehicleData current, int lo, int hi, VehicleData arr[]) {
    int large = 2 * lo + 1;
    int done = 0;
    while ((!done) && (large <= hi)) {
        if ((large < hi) && (arr[large].unpaidCount < arr[large + 1].unpaidCount)) {
            large++;
        }
        if (current.unpaidCount >= arr[large].unpaidCount) {
            done = 1;
        } else {
            arr[lo] = arr[large];
            lo = large;
            large = 2 * lo + 1;
        }
    }
    arr[lo] = current;
}

void BuildHeap(VehicleData arr[], int count) {
    int lo;
    for (lo = (count / 2) - 1; lo >= 0; lo--) {
        InsertHeap(arr[lo], lo, count - 1, arr);
    }
}

void heapsort(VehicleData arr[], int count) {
    int eu;
    VehicleData current_item;
    BuildHeap(arr, count);    
    for (eu = count - 1; eu >= 1; eu--) {
        current_item = arr[eu];
        arr[eu] = arr[0];
        InsertHeap(current_item, 0, eu - 1, arr);
    }
}

void countVehicles(Vehicle *p, int *count) {
    if (p != NULL) {
        countVehicles(p->left, count);
        (*count)++;
        countVehicles(p->right, count);
    }
}

void populateVehicleArray(Vehicle *p, VehicleData arr[], int *i) {
    if (p != NULL) {
        populateVehicleArray(p->left, arr, i);
        arr[*i].v = p;
        arr[*i].unpaidCount = 0;
        (*i)++;
        populateVehicleArray(p->right, arr, i);
    }
}

void scanViolationsForUnpaid(Violation *p, VehicleData arr[], int count) {
    if (p != NULL) {
        scanViolationsForUnpaid(p->left, arr, count);
        if (p->isPaid == false) {
            int i = 0;
            int found = 0;
            while (i < count && found == 0) {
                if (strcmp(arr[i].v->regNo, p->regNo) == 0) {
                    arr[i].unpaidCount++;
                    found = 1;
                }
                i++;
            }
        }
        scanViolationsForUnpaid(p->right, arr, count);
    }
}

void sortVehiclesByUnpaidCount(Vehicle *v, Violation *vio) {
    int count = 0;
    countVehicles(v, &count);
    if (count == 0) {
        printf("No vehicles registered.\n");
    } else {
        VehicleData *arr = (VehicleData*)malloc(count * sizeof(VehicleData));
        if (arr == NULL) {
            printf("Memory allocation failed.\n");
        } else {
            int i = 0;
            populateVehicleArray(v, arr, &i);
            scanViolationsForUnpaid(vio, arr, count);
            heapsort(arr, count);           
            printf("\nVehicles sorted by unpaid violations (Heap Sort):\n");
            for (int idx = count - 1; idx >= 0; idx--) {
                printf("\nRegistration Number: %s\n", arr[idx].v->regNo);
                printf("Owner Name: %s\n", arr[idx].v->name);
                printf("Contact Number: %lld\n", arr[idx].v->contactNo);
                printf("Address: %s\n", arr[idx].v->address);
                printf("Unpaid Violations: %d\n", arr[idx].unpaidCount);
                printf("Pending Amount: %.2f\n", arr[idx].v->pendingAmount);
            }
            free(arr);
        }
    }
    return;
}

void InsertLocationHeap(LocationData current, int lo, int hi, LocationData arr[]) {
    int large = 2 * lo + 1;
    int done = 0;
    while ((!done) && (large <= hi)) {
        if ((large < hi) && (arr[large].violationCount < arr[large + 1].violationCount)) {
            large++;
        }
        if (current.violationCount >= arr[large].violationCount) {
            done = 1;
        } else {
            arr[lo] = arr[large];
            lo = large;
            large = 2 * lo + 1;
        }
    }
    arr[lo] = current;
}

void BuildLocationHeap(LocationData arr[], int count) {
    int lo;
    for (lo = (count / 2) - 1; lo >= 0; lo--) {
        InsertLocationHeap(arr[lo], lo, count - 1, arr);
    }
}

void locationHeapSort(LocationData arr[], int count) {
    int eu;
    LocationData current_item;
    BuildLocationHeap(arr, count);    
    for (eu = count - 1; eu >= 1; eu--) {
        current_item = arr[eu];
        arr[eu] = arr[0];
        InsertLocationHeap(current_item, 0, eu - 1, arr);
    }
}

void countLocations(Location *p, int *count) {
    if (p != NULL) {
        countLocations(p->left, count);
        (*count)++;
        countLocations(p->right, count);
    }
}

void populateLocationArray(Location *p, LocationData arr[], int *i) {
    if (p != NULL) {
        populateLocationArray(p->left, arr, i);
        arr[*i].loc = p;
        arr[*i].violationCount = 0;
        arr[*i].totalRevenue = 0;
        (*i)++;
        populateLocationArray(p->right, arr, i);
    }
}

void scanViolationsForLocations(Violation *p, LocationData arr[], int count) {
    if (p != NULL) {
        scanViolationsForLocations(p->left, arr, count);
        int i = 0;
        int found = 0;
        while (i < count && found == 0) {
            if (strcmp(arr[i].loc->locId, p->locId) == 0) {
                arr[i].violationCount++;
                found = 1;
            }
            i++;
        }
        scanViolationsForLocations(p->right, arr, count);
    }
}

void sortLocationsByViolationCount(Location *loc, Violation *vio) {
    int count = 0;
    countLocations(loc, &count);
    if (count == 0) {
        printf("No locations available.\n");
    } else {
        LocationData *arr = (LocationData*)malloc(count * sizeof(LocationData));
        if (arr == NULL) {
            printf("Memory allocation failed.\n");
        } else {
            int i = 0;
            populateLocationArray(loc, arr, &i);
            scanViolationsForLocations(vio, arr, count);
            locationHeapSort(arr, count);           
            printf("\nLocations sorted by number of violations:\n");
            for (int idx = count - 1; idx >= 0; idx--) {
                printf("\nLocation ID: %s\n", arr[idx].loc->locId);
                printf("Location Name: %s\n", arr[idx].loc->locName);
                printf("Violation Count: %d\n", arr[idx].violationCount);
            }
            free(arr);
        }
    }
    return;
}

void InsertRevenueHeap(LocationData current, int lo, int hi, LocationData arr[]) {
    int large = 2 * lo + 1;
    int done = 0;

    while ((!done) && (large <= hi)) {
        if ((large < hi) && (arr[large].totalRevenue < arr[large + 1].totalRevenue)) {
            large++;
        }
        if (current.totalRevenue >= arr[large].totalRevenue) {
            done = 1;
        } else {
            arr[lo] = arr[large];
            lo = large;
            large = 2 * lo + 1;
        }
    }
    arr[lo] = current;
}

void BuildRevenueHeap(LocationData arr[], int count) {
    int lo;
    for (lo = (count / 2) - 1; lo >= 0; lo--) {
        InsertRevenueHeap(arr[lo], lo, count - 1, arr);
    }
}

void locationRevenueHeapSort(LocationData arr[], int count) {
    int eu;
    LocationData current_item;
    BuildRevenueHeap(arr, count);    
    for (eu = count - 1; eu >= 1; eu--) {
        current_item = arr[eu];
        arr[eu] = arr[0];
        InsertRevenueHeap(current_item, 0, eu - 1, arr);
    }
}

void scanViolationsForRevenue(Violation *p, LocationData arr[], int count) {
    if (p != NULL) {
        scanViolationsForRevenue(p->left, arr, count);
        int i = 0;
        int found = 0;
        while (i < count && found == 0) {
            if (strcmp(arr[i].loc->locId, p->locId) == 0) {
                arr[i].totalRevenue += p->amount;
                found = 1;
            }
            i++;
        }
        scanViolationsForRevenue(p->right, arr, count);
    }
}

void sortLocationsByRevenue(Location *loc, Violation *vio) {
    int count = 0;
    countLocations(loc, &count);
    if (count == 0) {
        printf("No locations available.\n");
    } else {
        LocationData *arr = (LocationData*)malloc(count * sizeof(LocationData));
        if (arr == NULL) {
            printf("Memory allocation failed.\n");
        } else {
            int i = 0;
            populateLocationArray(loc, arr, &i);
            scanViolationsForRevenue(vio, arr, count);
            locationRevenueHeapSort(arr, count);           
            printf("\nLocations sorted by total fine revenue:\n");
            for (int idx = count - 1; idx >= 0; idx--) {
                printf("\nLocation ID: %s\n", arr[idx].loc->locId);
                printf("Location Name: %s\n", arr[idx].loc->locName);
                printf("Total Fine Revenue: %.2f\n", arr[idx].totalRevenue);
            }
            free(arr);
        }
    }
    return;
}

void scanViolationsForTypes(Violation *p, ViolationData arr[]) {
    if (p != NULL) {
        scanViolationsForTypes(p->left, arr);
        // Assuming curr->vt maps directly to indices 0 to 3 or can be matched. 
        // Let's use direct indexing since vt acts as an enum.
        arr[p->vt].frequency++;
        scanViolationsForTypes(p->right, arr);
    }
}

void sortViolationTypes(Violation *vio){
    ViolationData arr[4];
    arr[0].vt = illegalpark;
    arr[1].vt = overspeed;
    arr[2].vt = redlightjump;
    arr[3].vt = helmetorbelt;
    for(int i = 0; i < 4; i++){
        arr[i].frequency = 0;
    }
    scanViolationsForTypes(vio, arr);
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3 - i; j++){
            if(arr[j].frequency < arr[j+1].frequency){
                ViolationData temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }   
    printf("\nViolation types sorted by frequency:\n");
    for(int i = 0; i < 4; i++){
        printf("\nViolation Type: ");
        switch(arr[i].vt){
            case illegalpark:
                printf("Illegal Parking");
                break;
            case overspeed:
                printf("Overspeeding");
                break;
            case redlightjump:
                printf("Red Light Jump");
                break;
            case helmetorbelt:
                printf("Helmet/Seatbelt Violation");
                break;
        }
        printf("\nFrequency: %d\n", arr[i].frequency);
    }
    return;
}

void scanViolationsForRepeatOffenders(Violation *p, Vehicle *v, ViolationRepeatData arr[]) {
    if (p != NULL) {
        scanViolationsForRepeatOffenders(p->left, v, arr);
        arr[p->vt].totalCount++;
        Vehicle *veh = searchVeh(p->regNo, v);
        if (veh != NULL && veh->numViolations > 2) {
            arr[p->vt].repeatCount++;
        }        
        scanViolationsForRepeatOffenders(p->right, v, arr);
    }
}

void sortViolationTypesByRepeatOffenders(Vehicle *v, Violation *vio){
    ViolationRepeatData arr[4];
    arr[0].vt = illegalpark;
    arr[1].vt = overspeed;
    arr[2].vt = redlightjump;
    arr[3].vt = helmetorbelt;
    for(int i = 0; i < 4; i++){
        arr[i].totalCount = 0;
        arr[i].repeatCount = 0;
        arr[i].fraction = 0;
    }
    scanViolationsForRepeatOffenders(vio, v, arr);
    for(int i = 0; i < 4; i++){
        if(arr[i].totalCount != 0){
            arr[i].fraction = (float)arr[i].repeatCount / arr[i].totalCount;
        }
    }
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3 - i; j++){
            if(arr[j].fraction < arr[j+1].fraction){
                ViolationRepeatData temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    printf("\nViolation types ranked by repeat-offender fraction:\n");
    for(int i = 0; i < 4; i++){
        printf("\nViolation Type: ");
        switch(arr[i].vt){
            case illegalpark:
                printf("Illegal Parking");
                break;
            case overspeed:
                printf("Overspeeding");
                break;
            case redlightjump:
                printf("Red Light Jump");
                break;
            case helmetorbelt:
                printf("Helmet/Seatbelt Violation");
                break;
        }
        printf("\nTotal Violations: %d\n", arr[i].totalCount);
        printf("Repeat-Offender Violations: %d\n", arr[i].repeatCount);
        printf("Fraction: %.2f\n", arr[i].fraction);
    }
    return;
}

void displayVehiclesByThresholdHelper(Vehicle *p, int threshold, int *found) {
    if (p != NULL) {
        displayVehiclesByThresholdHelper(p->left, threshold, found);
        if (p->numViolations >= threshold) {
            printf("\nRegistration Number: %s\n", p->regNo);
            printf("Owner Name: %s\n", p->name);
            printf("Contact Number: %lld\n", p->contactNo);
            printf("Address: %s\n", p->address);
            printf("Total Violations: %d\n", p->numViolations);
            *found = 1;
        }        
        displayVehiclesByThresholdHelper(p->right, threshold, found);
    }
}

void displayVehiclesByThreshold(Vehicle *v){
    int threshold;
    printf("Enter violation count threshold: ");
    scanf("%d", &threshold);
    int found = 0;
    displayVehiclesByThresholdHelper(v, threshold, &found);   
    if(found == 0){
        printf("No vehicles found meeting the threshold.\n");
    }
    return;
}

void displayPendingViolationsHelper(Violation *p, char *targetRegNo, int *found) {
    if (p != NULL) {
        displayPendingViolationsHelper(p->left, targetRegNo, found);
        if (strcmp(p->regNo, targetRegNo) == 0 && p->isPaid == false) {
            printf("\nViolation ID: %s\n", p->vioId);
            printf("Violation Type: ");
            switch (p->vt) {
                case illegalpark:
                    printf("Illegal Parking");
                    break;
                case overspeed:
                    printf("Overspeeding");
                    break;
                case redlightjump:
                    printf("Red Light Jump");
                    break;
                case helmetorbelt:
                    printf("Helmet/Seatbelt Violation");
                    break;
            }
            printf("\nLocation ID: %s\n", p->locId);
            printf("Date: %02d/%02d/%04d\n", p->d.day, p->d.month, p->d.year);
            printf("Time: %02d:%02d:%02d\n", p->t.hour, p->t.min, p->t.sec);
            printf("Fine Amount: %.2f\n", p->amount);
            *found = 1;
        }        
        displayPendingViolationsHelper(p->right, targetRegNo, found);
    }
}

void displayPendingViolations(Vehicle *v, Violation *vio) {
    char regNo[maxlen];
    printf("Enter vehicle registration number: ");
    scanf("%s", regNo);
    uppercase(regNo);
    Vehicle *owner = searchVeh(regNo, v);
    if (owner == NULL) {
        printf("Vehicle not found.\n");
    } else {
        int found = 0;
        displayPendingViolationsHelper(vio, regNo, &found);       
        if (found == 0) {
            printf("No pending violations found for this vehicle.\n");
        }
    }
    return;
}

void InsertPendingHeap(VehiclePendingData current, int lo, int hi, VehiclePendingData arr[]) {
    int large = 2 * lo + 1;
    int done = 0;
    while ((!done) && (large <= hi)) {
        if ((large < hi) && (arr[large].pendingAmount < arr[large + 1].pendingAmount)) {
            large++;
        }
        if (current.pendingAmount >= arr[large].pendingAmount) {
            done = 1;
        } else {
            arr[lo] = arr[large];
            lo = large;
            large = 2 * lo + 1;
        }
    }
    arr[lo] = current;
}

void BuildPendingHeap(VehiclePendingData arr[], int count) {
    int lo;
    for (lo = (count / 2) - 1; lo >= 0; lo--) {
        InsertPendingHeap(arr[lo], lo, count - 1, arr);
    }
}

void vehiclePendingHeapSort(VehiclePendingData arr[], int count) {
    int eu;
    VehiclePendingData current_item;
    BuildPendingHeap(arr, count);    
    for (eu = count - 1; eu >= 1; eu--) {
        current_item = arr[eu];
        arr[eu] = arr[0];
        InsertPendingHeap(current_item, 0, eu - 1, arr);
    }
}

void populateVehiclePendingArray(Vehicle *p, VehiclePendingData arr[], int *i) {
    if (p != NULL) {
        populateVehiclePendingArray(p->left, arr, i);
        arr[*i].v = p;
        arr[*i].pendingAmount = p->pendingAmount;
        (*i)++;
        populateVehiclePendingArray(p->right, arr, i);
    }
}

void sortVehiclesByPendingAmount(Vehicle *v) {
    int n = 0;
    countVehicles(v, &n);
    if (n == 0) {
        printf("No vehicles registered.\n");
    } else {
        VehiclePendingData *arr = (VehiclePendingData*)malloc(n * sizeof(VehiclePendingData));
        if (arr == NULL) {
            printf("Memory allocation failed.\n");
        } else {
            int i = 0;
            populateVehiclePendingArray(v, arr, &i);
            vehiclePendingHeapSort(arr, n);           
            printf("\nVehicles sorted by pending fine amount (descending):\n");
            for (int idx = n - 1; idx >= 0; idx--) {
                printf("\nRegistration Number: %s\n", arr[idx].v->regNo);
                printf("Owner Name: %s\n", arr[idx].v->name);
                printf("Pending Amount: %.2f\n", arr[idx].pendingAmount);
                printf("\n");
            }
            free(arr);
        }
    }
    return;
}

void displayPaymentHistory(Transactions *t){
    if(t==NULL || t->top==NULL){
        printf("No payment history available.\n");
    }else{
        Node *curr=t->top;
        if(curr==NULL){
            printf("No payment history available.\n");
        }else{
            printf("\nComplete Payment History:\n");
            while(curr!=NULL){
                printf("\nTransaction ID: %s\n",curr->transactionId);
                printf("Violation ID: %s\n",curr->v->vioId);
                printf("Amount Paid: %.2f\n",curr->amountpaid);
                if(curr->payMode==online){
                    printf("Payment Mode: Online\n");
                }else{
                    printf("Payment Mode: Cash\n");
                }
                printf("Payment Date: ");
                printf("%d/%d/%d\n", curr->payDate.day, curr->payDate.month, curr->payDate.year);
                curr=curr->next;
            }
        }
    }
    return;
}

void loadVehicles(Vehicle **v, int *check) {
    FILE *fp;
    Vehicle *nptr;
    int flag = 1;
    fp = fopen("vehicles.txt", "r");
    if(fp == NULL){
        *check = 1;
        return;
    }
    while(flag == 1){
        nptr = (Vehicle*)malloc(sizeof(Vehicle));
        if(nptr == NULL){
            *check = 1;
            flag = 0;
        }
        else if(fscanf(fp, "%s %s %lld %s %f %f %f %d",
            nptr->regNo, nptr->name, &nptr->contactNo,
            nptr->address, &nptr->totalFines, &nptr->paidFines,
            &nptr->pendingAmount, &nptr->numViolations) != 8){
            free(nptr);
            flag = 0;
        }
        else{
            nptr->left = NULL;
            nptr->right = NULL;
            nptr->height = 1;
            
            *v = insertVehicle(*v, nptr);
        }
    }
    fclose(fp);
    return;
}

void loadViolations(Violation **v, int *check){
    FILE *fp;
    Violation *nptr;
    int flag = 1;
    int vt, paid;
    fp = fopen("violations.txt", "r");
    if(fp == NULL){
        *check = 1;
        return;
    }
    while(flag == 1){
        nptr = (Violation*)malloc(sizeof(Violation));
        if(nptr == NULL){
            *check = 1;
            flag = 0;
        }
        else if(fscanf(fp, "%s %s %d %s %d %d %d %d %d %d %d %f",
            nptr->vioId, nptr->regNo, &vt, nptr->locId,
            &nptr->d.day, &nptr->d.month, &nptr->d.year,
            &nptr->t.hour, &nptr->t.min, &nptr->t.sec,
            &paid, &nptr->amount) != 12){
            free(nptr);
            flag = 0;
        }
        else{
            nptr->vt = (Viotype)vt;
            nptr->isPaid = (bool)paid;
            nptr->left = NULL;
            nptr->right = NULL;
            nptr->height = 1;
            
            *v = insertViolation(*v, nptr);
        }
    }
    fclose(fp);
    return;
}

void loadLocations(Location **l, int *check){
    FILE *fp;
    Location *nptr;
    int flag = 1;
    fp = fopen("locations.txt", "r");
    if(fp == NULL){
        *check = 1;
        return;
    }
    while(flag == 1){
        nptr = (Location*)malloc(sizeof(Location));
        if(nptr == NULL){
            *check = 1;
            flag = 0;
        }
        else if(fscanf(fp, "%s %s", nptr->locId, nptr->locName) != 2){
            free(nptr);
            flag = 0;
        }
        else{
            nptr->left = NULL;
            nptr->right = NULL;
            nptr->height = 1;
            
            *l = insertLocation(*l, nptr);
        }
    }
    fclose(fp);
    return;
}

void loadTransactions(Transactions **tr, Violation *vio, int *check){
    FILE *fp = fopen("transactions.txt", "r");
    Node *nptr, *curr;
    char vioId[maxlen];
    int mode, flag = 1;
    if (fp == NULL){
        *check = 1;
    }
    else{
        while(flag == 1){
            nptr=(Node *)malloc(sizeof(Node));
            if (nptr==NULL){
                *check=1;
                flag=0;
            }else if(fscanf(fp, "%s %s %f %d %d %d %d",
                            nptr->transactionId, vioId,
                            &nptr->amountpaid, &mode,
                            &nptr->payDate.day, &nptr->payDate.month,
                            &nptr->payDate.year) != 7)
            {
                free(nptr);
                flag = 0;
            }
            else{
                nptr->v = searchViolation(vioId, vio);
                if (nptr->v == NULL){
                    free(nptr);
                    *check = 1;
                    flag = 0;
                }else{
                    nptr->payMode = (Mode)mode;
                    nptr->next = NULL;
                    if((*tr)->top==NULL){
                        (*tr)->top = nptr;
                    }else{
                        curr=(*tr)->top;
                        while(curr->next != NULL){
                            curr = curr->next;
                        }
                        curr->next = nptr;
                    }
                }
            }
        }
        fclose(fp);
    }
}

void writeVehicleHelper(Vehicle *p, FILE *fp, int *check) {
    if (p != NULL) {
        writeVehicleHelper(p->left, fp, check);
        
        if (fprintf(fp, "%s %s %lld %s %f %f %f %d\n",
            p->regNo, p->name, p->contactNo,
            p->address, p->totalFines, p->paidFines,
            p->pendingAmount, p->numViolations) < 0) {
            *check = 1;
        }
        
        writeVehicleHelper(p->right, fp, check);
    }
}

void overwriteVehicles(Vehicle *v, int *check) {
    FILE *fp = fopen("vehicles.txt", "w");
    if (fp == NULL) {
        *check = 1;
        return;
    }   
    writeVehicleHelper(v, fp, check);
    
    fclose(fp);
    return;
}

void writeViolationHelper(Violation *p, FILE *fp, int *check) {
    if (p != NULL) {
        writeViolationHelper(p->left, fp, check);
        if (fprintf(fp, "%s %s %d %s %d %d %d %d %d %d %d %f\n",
            p->vioId, p->regNo, p->vt, p->locId,
            p->d.day, p->d.month, p->d.year,
            p->t.hour, p->t.min, p->t.sec,
            p->isPaid, p->amount) < 0) {
            *check = 1;
        }
        writeViolationHelper(p->right, fp, check);
    }
}

void overwriteViolations(Violation *vio, int *check) {
    FILE *fp = fopen("violations.txt", "w");
    if (fp == NULL) {
        *check = 1;
    } else {
        writeViolationHelper(vio, fp, check);
        fclose(fp);
    }
    return;
}

void writeLocationHelper(Location *p, FILE *fp, int *check) {
    if (p != NULL) {
        writeLocationHelper(p->left, fp, check);
        if (fprintf(fp, "%s %s\n", p->locId, p->locName) < 0) {
            *check = 1;
        }
        writeLocationHelper(p->right, fp, check);
    }
}

void overwriteLocations(Location *loc, int *check) {
    FILE *fp = fopen("locations.txt", "w");
    if (fp == NULL) {
        *check = 1;
    } else {
        writeLocationHelper(loc, fp, check);
        fclose(fp);
    }
    return;
}

void overwriteTransactions(Transactions *t, int *check){
    FILE *fp = fopen("transactions.txt", "w");
    Node *curr = t->top;
    Node *arr[1000];
    int count = 0, i;
    if (fp == NULL){
        *check = 1;
    }else{
        while (curr!=NULL && count<1000){
            arr[count] = curr;
            count++;
            curr = curr->next;
        }
        for (i = count - 1; i >= 0; i--){
            fprintf(fp, "%s %s %f %d %d %d %d\n",
                    arr[i]->transactionId, arr[i]->v->vioId,
                    arr[i]->amountpaid, arr[i]->payMode,
                    arr[i]->payDate.day, arr[i]->payDate.month,
                    arr[i]->payDate.year);
        }
        fclose(fp);
    }
}

void printLocationsHelper(Location *p) {
    if (p != NULL) {
        printLocationsHelper(p->left);
        printf("Location ID: %s\n", p->locId);
        printf("Location Name: %s\n", p->locName);
        printf("\n");
        printLocationsHelper(p->right);
    }
}

void printLocations(Location *loc){
    if(loc == NULL){
        printf("No locations available.\n");
    } else {
        printLocationsHelper(loc);
    }
    return;
}

Vehicle* insertVehicle(Vehicle *v, Vehicle *nptr) {
    return insertvehicle(v, nptr);
}

Location* insertLocation(Location *l, Location *nptr) {
    Location *result = l;
    Location *p = l;
    if (p == NULL) {
        nptr->left = NULL;
        nptr->right = NULL;
        nptr->height = 1;
        result = nptr;
    } else {
        int cmp = strcmp(nptr->locId, p->locId);
        if (cmp < 0) {
            p->left = insertLocation(p->left, nptr);
            result = p;
        } else if (cmp > 0) {
            p->right = insertLocation(p->right, nptr);
            result = p;
        } else {
            printf("Location with this ID already exists.\n");
            free(nptr);
            result = p;
        }
        if (cmp != 0) {
            p->height = getMax(locationHeight(p->left), locationHeight(p->right)) + 1;
            int balance = getLocationBalance(p);
            if (balance > 1 && getLocationBalance(p->left) >= 0) {
                result = rotateRightLocation(p);
            }
            else if (balance < -1 && getLocationBalance(p->right) <= 0) {
                result = rotateLeftLocation(p);
            }
            else if (balance > 1 && getLocationBalance(p->left) < 0) {
                p->left = rotateLeftLocation(p->left);
                result = rotateRightLocation(p);
            }
            else if (balance < -1 && getLocationBalance(p->right) > 0) {
                p->right = rotateRightLocation(p->right);
                result = rotateLeftLocation(p);
            } else {
                result = p;
            }
        }
    }
    return result;
}

int compareViolationTime(Violation *a, Violation *b) {
    int result = 0;
    if (a->d.year != b->d.year) {
        result = a->d.year - b->d.year;
    } else if (a->d.month != b->d.month) {
        result = a->d.month - b->d.month;
    } else if (a->d.day != b->d.day) {
        result = a->d.day - b->d.day;
    } else if (a->t.hour != b->t.hour) {
        result = a->t.hour - b->t.hour;
    } else if (a->t.min != b->t.min) {
        result = a->t.min - b->t.min;
    } else {
        result = a->t.sec - b->t.sec;
    }
    return result;
}

void countRangeViolations(Violation *root, char *V1, char *V2, int *count) {
    if (root != NULL) {
        if (strcmp(root->vioId, V1) > 0) {
            countRangeViolations(root->left, V1, V2, count);
        }
        if (strcmp(root->vioId, V1) >= 0 && strcmp(root->vioId, V2) <= 0) {
            (*count)++;
        }
        if (strcmp(root->vioId, V2) < 0) {
            countRangeViolations(root->right, V1, V2, count);
        }
    }
}

void collectRangeViolations(Violation *root, char *V1, char *V2, Violation **arr, int *index) {
    if (root != NULL) {
        if (strcmp(root->vioId, V1) > 0) {
            collectRangeViolations(root->left, V1, V2, arr, index);
        }
        if (strcmp(root->vioId, V1) >= 0 && strcmp(root->vioId, V2) <= 0) {
            arr[*index] = root;
            (*index)++;
        }
        if (strcmp(root->vioId, V2) < 0) {
            collectRangeViolations(root->right, V1, V2, arr, index);
        }
    }
}

void displayRangeViolationsChronological(Violation *root, char *V1, char *V2) {
    int count = 0;
    countRangeViolations(root, V1, V2, &count);
    if (count == 0) {
        printf("No violations found between ID %s and %s.\n", V1, V2);
    } else {
        Violation **arr = (Violation **)malloc(count * sizeof(Violation *));
        if (arr == NULL) {
            printf("Memory allocation failed for pointer array!\n");
        } else {
            int index = 0;
            collectRangeViolations(root, V1, V2, arr, &index);
            for (int i = 0; i < count - 1; i++) {
                for (int j = 0; j < count - i - 1; j++) {
                    if (compareViolationTime(arr[j], arr[j + 1]) > 0) {
                        Violation *temp = arr[j];
                        arr[j] = arr[j + 1];
                        arr[j + 1] = temp;
                    }
                }
            }
            printf("\n--- Violations from ID %s to %s (Sorted Chronologically) ---\n", V1, V2);
            for (int i = 0; i < count; i++) {
                printf("Violation ID: %s | Reg No: %s | Date: %02d/%02d/%d | Time: %02d:%02d:%02d\n",
                       arr[i]->vioId, arr[i]->regNo,
                       arr[i]->d.day, arr[i]->d.month, arr[i]->d.year,
                       arr[i]->t.hour, arr[i]->t.min, arr[i]->t.sec);
            }
            free(arr);
        }
    }
}