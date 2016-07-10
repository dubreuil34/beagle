// ---------------------------------------------------------------------
// exemple-periodique-01.c
// Fichier d'exemple du livre "Solutions Temps-Reel sous Linux"
// (C) 2012-2015 - Christophe BLAESS
// http://christophe.blaess.fr
// ---------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

#include <native/task.h>
#include <native/timer.h>
#include <rtdk.h>

#include "lib/beagle.h"

int gpio;

void fonction_periodique (void * arg)
{
	int err;
	unsigned long depassements;
	
	// rend le thread periodique
	// a partir de TM_NOW
	// periode en nanosecondes
	rt_task_set_periodic(rt_task_self(), TM_NOW,  500000);
	
	// printf pour xenomai
	rt_printf("[%lld] Timer programmé...\n", rt_timer_read());
	// rt_task_wait_period 
	// attend le reveil
	// depassement : permet de savoir si on a manqué des reveils
	while ((err = rt_task_wait_period(& depassements)) == 0) {
		GPIO_Toggle(gpio);
		//rt_printf("[%lld]", rt_timer_read());
		if (depassements != 0)
			rt_printf(" Depassements : %lu\n", depassements);
		//rt_printf("\n");
	}
	fprintf(stderr, "rt_task_wait_period(): %s\n",strerror(-err));
	exit(EXIT_FAILURE);
}



int main()
{
	RT_TASK task;
	
	// bloque la memoire virtuelle pour ne pas avoir de swap
	mlockall(MCL_CURRENT|MCL_FUTURE);
			
	//
	rt_print_auto_init(1);

	gpio=GPIOSetup("P9_12","out");

	// spawn : cree et lance la tache : equiv rt_task_create + rt_task_start
	if (rt_task_spawn(& task, NULL, 0, 99,
	        T_JOINABLE, fonction_periodique, NULL) != 0) {
		fprintf(stderr, "Impossible de creer la tache\n");
		exit(EXIT_FAILURE);
	}

	rt_task_join(& task);
	return 0;
}


