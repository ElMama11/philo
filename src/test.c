/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 14:54:44 by mverger           #+#    #+#             */
/*   Updated: 2022/04/24 18:24:37 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"
#  define psleep(sec) sleep ((sec))
 
#define INITIAL_STOCK   20
#define NB_CLIENTS      5
 
 
static pthread_mutex_t  mutex = PTHREAD_MUTEX_INITIALIZER;

void * fonction_thread (void * arg)
{
        int numero = (int) arg;
        //usleep(10000 * numero);
        while (1) {
                fprintf(stderr, "[%d] demande le mutex\n", numero);
                pthread_mutex_lock(& mutex);
                fprintf(stderr, "        [%d] tient le mutex\n", numero);
                sleep(1);
                fprintf(stderr, "[%d] lache le mutex\n", numero);
                pthread_mutex_unlock(& mutex);
                usleep(10000);
        }
        return NULL;
}

#define NB_THREADS 5
int main(void)
{
        int i;
        pthread_t thread[NB_THREADS];

        pthread_mutex_lock(& mutex);
        for (i = 0; i < NB_THREADS; i ++)
                pthread_create(& thread[i], NULL, fonction_thread, (void *) (i+1));
        sleep(1);
        fprintf(stderr, "Liberation initiale du mutex\n");
       pthread_mutex_unlock(& mutex);
        for (i = 0; i < NB_THREADS; i ++)
                pthread_join(thread[i], NULL);
        return EXIT_SUCCESS;
}