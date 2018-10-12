#include "user.h"

static bool is_buffer_same(struct _BUFFER* p, struct _BUFFER* n){
	
	if (p != NULL  && n != NULL){
		
		if (p->len == n->len){
			
			for (U16 index = 0; index < p->len; index ++){
				if (p->buffer[index] != n->buffer[index])
					return false;
			}
			
			return true;
		}
	}
	
	return false;
}

PBUFFER init_buffer(PBUFFER buf, U16 len, void* data){
	
	if (buf != NULL){
		
		buf->len = len;
		buf->buffer = data;
		
		buf->is = is_buffer_same;
	}
	
	return buf;
}