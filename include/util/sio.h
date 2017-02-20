typedef struct {
	Vector* conn;

} SIO;

typedef struct {

} SIOConnection;

SIO* sio_create();

int sio_register(SIO* sio, SIOState* sios);

int sio_unregister(SIOState* ptr);

void sio_loop(SIO* self);

int sio_destroy(SIO* self);

#define SIO_STATE_FUNC(func_name) int func_name(SIOState* sio)
typedef int (* sio_state_func)(SIOState* sio);

typedef enum {
	SIO_TIMERSTATE_INIT,
	SIO_TIMERSTATE_DIRTY,
	SIO_TIMERSTATE_TIMEOUT,
} TimerState;

typedef struct {
	TimerState state;
	int64_t time;
	int64_t expire;
} Timer;

static Timer* timer(int64_t time, int64_t expire);

typedef struct {
	sio_statefunc prev;
	sio_statefunc current;
	ssize_t size;
	sio_statefunc next;
	sio_statefunc error;
	Timer* timer;
} SIOState;
