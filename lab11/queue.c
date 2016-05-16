/* queue.c 
 *
 * A circular queue data structure
 * 
 * Filename: queue.c
 * Description: 
 * Author: Bryce Himebaugh
 * Maintainer: 
 * Created: Thu Feb  7 19:49:26 2013 (-0500)
 * Version: 
 * Last-Updated: 4/5/2016
 *           By: Max McLennan (mpmclenn)
 *               Won Yong Ha  (woha)
 *     Update #: 0
 * URL: 
 * Doc URL: 
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change Log:
 * 
 * 
 */

/* This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth
 * Floor, Boston, MA 02110-1301, USA.
 */

/* Code: */

#include "queue.h"

// We say that a queue is...
// - full when head is equal to tail
// - empty when head exactly one ahead of tail

void init_queue(queue_t *q) {
  q->head = 1;
  q->tail = 0;
  int i;
  for (i = 0; i < QUEUE_SIZE; i++) {
    q->buffer[i] = 0;
  }
}

int enqueue (queue_t *q, int data) {
  if (q->head == q->tail) {
    // fail
    return 0;
  }
  q->buffer[q->head] = data;
  q->head = (q->head + 1) % QUEUE_SIZE;
  return 1;
}

int dequeue (queue_t *q) {
  if (queue_empty(q)) {
    // fail
    return 0;
  }

  int nextTailIdx = (q->tail + 1) % QUEUE_SIZE;
  int result = q->buffer[nextTailIdx];
  q->tail = nextTailIdx;

  return result;
}

int queue_empty(queue_t *q) {
  int incrementedTail = (q->tail + 1) % QUEUE_SIZE;
  return incrementedTail == q->head;
}


/* queue.c ends here */
