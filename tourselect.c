/* Tournamenet Selections routines */

# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include "global.h"
# include "rand.h"

/* Routine for tournament selection, it creates a new_pop from old_pop by performing tournament selection and the crossover */
void selection (population *old_pop, population *new_pop, problem_instance *pi)
{
    int *a1, *a2;
    int temp;
    int i;
    int rand;
    individual *parent1, *parent2;
    a1 = (int *)malloc(popsize*sizeof(int));
    a2 = (int *)malloc(popsize*sizeof(int));

    /* Se inicializan vectores con individuos */
    for (i=0; i<popsize; i++)
    {
        a1[i] = a2[i] = i;
    }

    /*Se hacen swaps aleatoreos para ordenar cada arreglo */
    for (i=0; i<popsize; i++)
    {
        rand = rnd (i, popsize-1);
        temp = a1[rand];
        a1[rand] = a1[i];
        a1[i] = temp;

        rand = rnd (i, popsize-1);
        temp = a2[rand];
        a2[rand] = a2[i];
        a2[i] = temp;
    }
    for (i=0; i<popsize; i+=4)
    {
        /* Se crean dos hijos considerando los padres de a 1. Se ven los dos mejores padres sucecivos */
        parent1 = tournament (&old_pop->ind[a1[i]], &old_pop->ind[a1[i+1]]);
        parent2 = tournament (&old_pop->ind[a1[i+2]], &old_pop->ind[a1[i+3]]);
        crossover (parent1, parent2, &new_pop->ind[i], &new_pop->ind[i+1], pi);
        parent1 = tournament (&old_pop->ind[a2[i]], &old_pop->ind[a2[i+1]]);
        parent2 = tournament (&old_pop->ind[a2[i+2]], &old_pop->ind[a2[i+3]]);
        crossover (parent1, parent2, &new_pop->ind[i+2], &new_pop->ind[i+3], pi);
    }
    free (a1);
    free (a2);
    return;
}

/* Routine for binary tournament */
individual* tournament (individual *ind1, individual *ind2)
{
    int flag;
    flag = check_dominance (ind1, ind2);
    if (flag==1)
    {
        return (ind1);
    }
    if (flag==-1)
    {
        return (ind2);
    }
    if (ind1->crowd_dist > ind2->crowd_dist)
    {
        return(ind1);
    }
    if (ind2->crowd_dist > ind1->crowd_dist)
    {
        return(ind2);
    }
    if ((randomperc()) <= 0.5)
    {
        return(ind1);
    }
    else
    {
        return(ind2);
    }
}
