#include <stdint.h>
#include <unistd.h>
#include <util/list.h>
#include <malloc.h>

#include <util/sio.h>
#include <util/vector.h>
#include <sys/time.h>

static SIO_STATE_FUNC(noop) {
	return 0;
}

static int64_t timestamp_ms() {
	struct timeval te;
	gettimeofday(&te, NULL);
	return te.tv_sec * 1000LL + te.tv_usec / 1000;
}

SIO* sio_create() {
	return calloc(1, sizeof(SIO));
}

int sio_register(SIO* sio, SIOState* sios) {
	sios->timer ?: noop;
	sios->current ?: noop;
	sios->next ?: noop;
	sios->prev ?: noop;
	return vector_add(sio->conn, sios);
}

int sio_unregister(SIOState* ptr) {
	return 0;
}

static void timer_update(SIOState* sios, int64_t time) {
	Timer* self = sios->timer;
	switch(self->state) {
		case SIO_TIMERSTATE_INIT:
			self->time = time;
			self->state = SIO_TIMERSTATE_DIRTY;
			break;

		case SIO_TIMERSTATE_DIRTY:
			if(time - self->time >= self->expire)
				self->state = SIO_TIMERSTATE_TIMEOUT;
			else
				self->time = time;
			break;

		case SIO_TIMERSTATE_TIMEOUT:
			sios->error(sios);
			break;
	}
}


void sio_loop(SIO* self) {
	for(;;) {
		int64_t epoch_ms = timestamp_ms();
		for(int i = 0; i < self->conn->index; ++i) {
			SIOState* sios = self->conn->array[i];
			timer_update(sios, epoch_ms);
		}
	}
}

static Timer* timer(int64_t time, int64_t expire) {
	Timer* t = calloc(1, sizeof(Timer));
	t->time = time;
	t->expire = expire > 0 ? expire : -1;
	return t;
}

int sio_destroy(SIO* self) {
	VectorIterator con;
	vector_iterator_init(&con, self->conn);
	while(vector_iterator_has_next(&con)) {
		SIOState* sios = vector_iterator_next(&con);
		sio_unregister(sios);
	}
	return 0;
}