/*****************************************
* Copyright (C) 2020 * Ltd. All rights reserved.
* 
* File name   : xservice_hsm_mgr.c
* Author      : longbin
* Created date: 2020-08-24 15:08:52
* Description : 
*
*******************************************/

#include <cstdio>
#include <cassert>
#include "xservice_hsm_mgr_impl.h"
#include "hsm_engine.h"

//expand macro and implement the function get_XSERVICE_MGR_HSM_Defn()
#include "hsm_helper_define.h"

/*
 * implement declared functions auto-generated by gen_hsm here
 */
void onError(const HSM_StateChart_T& statechart) {
    XServiceHsmObject_T * pobj = (XServiceHsmObject_T *)statechart.userObj;
    char data = *(char *)statechart.eventdata.data();
    printf("\r[%d-%s] [%s]: Invalid char %d(%c)\n",
            statechart.currentStateId, statechart.currentStateName.c_str(),
            __func__, data, data);
    printf("\t\thas ignored, please continue input\n");
    printf("%s", pobj->working_data.c_str()); fflush(stdout);
}

void onInterupt1(const HSM_StateChart_T& statechart) {
    XServiceHsmObject_T * pobj = (XServiceHsmObject_T *)statechart.userObj;
    printf("\n%s entry reading dec:%s, str:%s\n", __func__, pobj->working_data.c_str(), pobj->extra_data.c_str());
}

void onInterupt2(const HSM_StateChart_T& statechart) {
    XServiceHsmObject_T * pobj = (XServiceHsmObject_T *)statechart.userObj;
    printf("\n%s exit reading dec:%s, str:%s\n", __func__, pobj->working_data.c_str(), pobj->extra_data.c_str());
}

void proc_close(const HSM_StateChart_T& statechart) {
    XServiceHsmObject_T * pobj = (XServiceHsmObject_T *)statechart.userObj;
    pobj->extra_data.clear();
    printf("\n%s extra data has been cleared\n", __func__);
}

void proc_decimal(const HSM_StateChart_T& statechart) {
    XServiceHsmObject_T * pobj = (XServiceHsmObject_T *)statechart.userObj;
    char data = *(char *)statechart.eventdata.data();
    pobj->working_data += (data);
    printf("\r[%d-%s] [%s]: Validity char %d(%c)\n",
            statechart.currentStateId, statechart.currentStateName.c_str(),
            __func__, data, data);
    printf("\tvalidity, you can continue type 0123456789\n");
    printf("%s", pobj->working_data.c_str()); fflush(stdout);
}

void proc_dot(const HSM_StateChart_T& statechart) {
    XServiceHsmObject_T * pobj = (XServiceHsmObject_T *)statechart.userObj;
    char data = *(char *)(statechart.eventdata.data());
    pobj->working_data += (data);
    printf("\r[%d-%s] [%s]: Validity char %d(%c)\n",
            statechart.currentStateId, statechart.currentStateName.c_str(),
            __func__, data, data);
    printf("\tuncompleted, you can continue type 0123456789\n");
    printf("%s", pobj->working_data.c_str()); fflush(stdout);
}

void proc_int(const HSM_StateChart_T& statechart) {
    XServiceHsmObject_T * pobj = (XServiceHsmObject_T *)statechart.userObj;
    char data = *(char *)(statechart.eventdata.data());
    pobj->working_data += (data);
    printf("\r[%d-%s] [%s]: Validity char %d(%c)\n",
            statechart.currentStateId, statechart.currentStateName.c_str(),
            __func__, data, data);
    printf("\tvalidity, you can continue type 0123456789.\n");
    printf("%s", pobj->working_data.c_str()); fflush(stdout);
}

void proc_lead0(const HSM_StateChart_T& statechart) {
    XServiceHsmObject_T * pobj = (XServiceHsmObject_T *)statechart.userObj;
    char data = *(char *)(statechart.eventdata.data());
    pobj->working_data += (data);
    printf("\r[%d-%s] [%s]: Validity char %d(%c)\n",
            statechart.currentStateId, statechart.currentStateName.c_str(),
            __func__, data, data);
    printf("\tvalidity, you can continue type .\n");
    printf("%s", pobj->working_data.c_str()); fflush(stdout);
}

void proc_open(const HSM_StateChart_T& statechart) {
    XServiceHsmObject_T * pobj = (XServiceHsmObject_T *)statechart.userObj;
    pobj->extra_data.clear();
    printf("%s please input your string\n", __func__);
}

void proc_reading(const HSM_StateChart_T& statechart) {
    XServiceHsmObject_T * pobj = (XServiceHsmObject_T *)statechart.userObj;
    char data = *(char *)(statechart.eventdata.data());
    pobj->extra_data += (data);
    printf("\r[%d-%s] [%s]: Validity char %d(%c)\n",
            statechart.currentStateId, statechart.currentStateName.c_str(),
            __func__, data, data);
    printf("%s", pobj->extra_data.c_str()); fflush(stdout);
}

void proc_signed(const HSM_StateChart_T& statechart) {
    XServiceHsmObject_T * pobj = (XServiceHsmObject_T *)statechart.userObj;
    char data = *(char *)(statechart.eventdata.data());
    pobj->working_data += (data);
    printf("\r[%d-%s] [%s]: Validity char %d(%c)\n",
            statechart.currentStateId, statechart.currentStateName.c_str(),
            __func__, data, data);
    printf("\tuncompleted, you can continue type 0123456789\n");
    printf("%s", pobj->working_data.c_str()); fflush(stdout);
}

void prompt_none(const HSM_StateChart_T& statechart) {
    (void)statechart;
    printf("Welcome, please type +-0123456789\n");
}

void prompt_reset(const HSM_StateChart_T& statechart) {
    (void)statechart;
    printf("restart, please type +-0123456789\n");
}

void resulted(const HSM_StateChart_T& statechart) {
    XServiceHsmObject_T * pobj = (XServiceHsmObject_T *)statechart.userObj;
    printf("\r[%d-%s] [%s]: %s\n",
            statechart.currentStateId, statechart.currentStateName.c_str(),
            __func__, pobj->working_data.c_str());
    pobj->working_data.clear();
}

bool isNumber1_9(const HSM_StateChart_T& statechart) {
    char data = *(char *)(statechart.eventdata.data());
    printf("\r[%d-%s] [%s]: %d(%c)\n",
            statechart.currentStateId, statechart.currentStateName.c_str(),
            __func__, data, data);
    return (data >= '1' && data <= '9');
}

std::string getEventName(int event) {
    switch (event) {
        EVENT2STRS
        default:
            break;
    } 
    return "unknown";
}


