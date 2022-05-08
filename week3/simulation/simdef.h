typedef enum SimStatusType { arrival, start, end } SimStatus;
typedef struct SimCustomerType
{
    SimStatus status;  
    int     arrivalTime;
    int     processTime;
    int     startTime;
    int     endTime;
    char    name;
    int     getService;
} SimCustomer;

