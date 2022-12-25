/*
 * PID.c
 *
 * Created: 4/11/2022 5:41:08 PM
 *  Author: hp
 */ 

#include "PID_interface.h"




void init_PID (PID_controller* pid, f32 kp,f32 ki,f32 kd,f32 lim_min ,f32 lim_max)
{
	//pid->T = T;
	//pid->to = to;
	
	pid->Kd = kd;
	pid->Ki = ki;
	pid->Kp = kp;
	
	pid->differentiator = 0;
	pid->integrator = 0;
	
	pid->pre_Error = 0;
	pid->pre_sensor_read = 0;
	
	
	pid->lim_max = lim_max;
	
	pid->lim_min = lim_min;
	
	
	
}

f32 PID_update(PID_controller* pid, f32 Setpoint , f32 Sensor_read,f32 Sample_time )
{
	
	
	
	
	f32 Error = Setpoint - Sensor_read ; 
	
	
	f32 proportional = Error*pid->Kp; //kp term
	
	
	
	float max_I,min_I;
	
	if (proportional > pid->lim_max )
	{
		max_I =  pid->lim_max - proportional;
	}
	else
	{
		max_I = 0;
	}
	
	if (proportional < pid->lim_min)
	{
		min_I= pid->lim_min - proportional;
	}
	else
	{
		min_I = 0;
	}	
	
	if (pid->integrator > max_I)
	{
		pid->integrator = max_I;
	}
	
	else if (pid->integrator < min_I)
	{
		pid->integrator = min_I;
	}	
	
	else
	{
		pid->integrator +=  pid->Ki * (Error+pid->pre_Error) ;
	}
	

	
	pid->differentiator = pid->Kd* (Sensor_read - pid->pre_sensor_read) / (Sample_time);
	
	
	
	pid->out = proportional + pid->differentiator +  pid->integrator;
	
	
	if (pid->lim_max < pid->out)
	{
		 pid->out = pid->lim_max;
	}
	
	if (pid->lim_min > pid->out)
	{
		pid->out = pid->lim_min;
	}	
	
	
	pid->pre_Error += Error;
	
	pid->pre_sensor_read = Sensor_read;
	
	
	
	return pid->out;

}
