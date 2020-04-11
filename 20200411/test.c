bool isValid(char * s) {
	staick char map[][2] = { {'(',')'}, {'[',']'}, {'{','}'} };
	while (*s) {
		int flag = 0;
		for (int i = 0; i < 3; i++) {
			if (*s == map[i][0]) {
				StackPush(&st);
				flag = 1;
				s++;
				break;
			}
		}
		if (flag == 0) {
			if (StrckEmpty)
				return false;
			char Topchar = StackTop;
			for (int i = 0; i < 3; i++) {
				if (*s == map[i][1]) {
					if (Topchar == map[i][0]) {
						StackPop(&st);
						s++;
						break;
					}
				}
				else {
					return false;
				}
			}
		}
	}
	if (StackEmpty(&sk))
		return true;
	return false;
}

//用队列实现栈
typedef struct {
	Queue q;
} MyStack;

MyStack* myStackCreate() {
	MyStack* ms = (MyStack*)malloc(sizeof(MyStack));
	queueInit(&ms->q);
	return ms;
}

void myStackPush(MyStack* obj, int x) {
	queuePush(&obj->q, x);

}

int myStackPop(MyStack* obj) {
	int ret;
	int size = queueSize(&obj->q);
	for (int i = 0; i < size - 1; i++) {
		int front = queueFront(&obj->q);
		queuePop(&obj->q);
		queuePush(&obj->q, front);
	}
	ret = queueFront(&obj->q);
	queuePop(&obj->q);
	return ret;
}

int myStackTop(MyStack* obj) {
	return queueBack(&obj->q);
}


bool myStackEmpty(MyStack* obj) {
	return queueEmpty(&obj->q);

}

void myStackFree(MyStack* obj) {
	queueDestory(&obj->q);
	free(obj);
}



//利用两个栈实现队列
typedef struct {
	Stack pushST;
	Stack popST;
} MyQueue;

MyQueue* myQueueCreate() {
	MyQueue* mq = (MyQueue*)malloc(sizeof(MyQueue));
	stackInit(&mq->pushST, 10);
	stackInit(&mq->popST, 10);
	return mq;
}

void myQueuePush(MyQueue* obj, int x) {
	stackPush(&obj->pushST, x);
}

int myQueuePop(MyQueue* obj) {
	int ret;
	if (stackEmpty(&obj->popST)) {
		while (stackEmpty(&obj->pushST) != 1) {
			int tmp = stackTop(&obj->pushST);
			stackPop(&obj->pushST);
			stackPush(&obj->popST, tmp);
		}
	}
	ret = stackTop(&obj->popST);
	stackPop(&obj->popST);
	return ret;
}

int myQueuePeek(MyQueue* obj) {
	if (stackEmpty(&obj->popST)) {
		while (stackEmpty(&obj->pushST) != 1) {
			int tmp = stackTop(&obj->pushST);
			stackPop(&obj->pushST);
			stackPush(&obj->popST, tmp);
		}
	}
	return stackTop(&obj->popST);
}

bool myQueueEmpty(MyQueue* obj) {
	return stackEmpty(&obj->pushST) && stackEmpty(&obj->popST);
}

void myQueueFree(MyQueue* obj) {
	stackDestory(&obj->pushST);
	stackDestory(&obj->popST);
	free(obj);

}
