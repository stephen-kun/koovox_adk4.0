/****************************************************************************
Copyright Cambridge Silicon Radio Limited 2004 - 2015.
Part of ADK 4.0

FILE NAME
    dm_page_timeout_handler.h
    
DESCRIPTION

*/

#ifndef    CONNECTION_DM_PAGE_TIMEOUT_HANDLER_H_
#define    CONNECTION_DM_PAGE_TIMEOUT_HANDLER_H_


/****************************************************************************
NAME    
    connectionHandleWritePageTimeout

DESCRIPTION
    Change the default page timeout used by the device 

RETURNS
    void
*/
void connectionHandleWritePageTimeout(CL_INTERNAL_DM_WRITE_PAGE_TIMEOUT_REQ_T *req);


#endif /* CONNECTION_DM_PAGE_TIMEOUT_HANDLER_H_ */
