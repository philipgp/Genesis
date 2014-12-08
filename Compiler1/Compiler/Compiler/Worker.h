#ifndef WORKER_H
#define WORKER_H 
#define MAX_WORKER_NAME_LEN 32
#define MAX_SERVICE_NAME_LEN 32
#define MAX_PARAMETER_NAME_LEN 32
#define MAX_SERVICE_LABEL_LEN MAX_SERVICE_NAME_LEN+MAX_WORKER_NAME_LEN+2
typedef struct wmProperty
{
	char m_szPropertyName[MAX_VARIABLE_LEN];
	int m_iDataType;
	struct ArrayDimension *m_LpDimension;
	struct WMProperty *m_LpNext;
}WMProperty;
typedef struct serviceParameter
{
	int m_iDataType;
	char m_szParameterName[MAX_PARAMETER_NAME_LEN];
	struct ServiceParameter *m_LpNext;
}ServiceParameter;
typedef struct Service
{
	char m_szServiceName[MAX_SERVICE_NAME_LEN],m_szFunctionLabel[MAX_FUNCTION_LABEL_LEN];
	struct ServiceParameter *m_LpInputParameter,m_LpOuputParameter;
	struct WorkerService *m_LpNext;
}WorkerService;
struct WorkerDefinition
{
	char m_szWorkerName[MAX_WORKER_NAME_LEN];
	struct WMProperty *m_LpMemberVar;
	struct WorkerService *m_LpService;
};
//void AddPropertyToWorker(char *LpszSymbolName)
#endif