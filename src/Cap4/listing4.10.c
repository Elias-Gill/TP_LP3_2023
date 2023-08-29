#include <malloc.h>

struct job {
  /* Link field for linked list.  */
  struct job *next;

  /* Other fields describing work to be done...  */
};

/* A linked list of pending  jobs.  */
struct job *job_queue;

void process_job(struct job *job) { return; }

/* Process queued jobs until the queue is empty.  */

void *thread_function(void *arg) {
  while (job_queue != NULL) {
    /* Get the next available job.  */
    struct job *next_job = job_queue;
    /* Remove this  job from  the  list.  */
    job_queue = job_queue->next;
    /* Carry out the work.  */
    process_job(next_job);
    /* Clean  up.  */
    free(next_job);
  }
  return NULL;
}

// Listing 4.10: Jobs Queue
int main(int argc, char *argv[]) {
  // TODO: implement
  return 0;
}
