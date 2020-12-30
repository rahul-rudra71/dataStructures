#ifndef stacks_for_regular_languages_h
#define stacks_for_regular_languages_h
#include "stack_p1.h"

class stacks_for_regular_languages {
	public:
		bool L1(char * inputString);
		bool L2(char * inputString);
		bool L3(char * inputString);
		bool L4(char * inputString);
};

bool stacks_for_regular_languages::L1(char *inputString) {
	stack_p1<char> s;

	while (*inputString != '\0') {
		//if stack is empty push to stack.
		if (s.isEmpty())
			s.push(*inputString);
		//if stack char is equal to current char push to stack 
		else if (s.peek() == *inputString)
			s.push(*inputString);
		//if stack char doesn't match current char pop stack
		else {
			s.pop();
		}
		++inputString;
	}

	//return whether stack is empty or not
	return s.isEmpty();
}

bool stacks_for_regular_languages::L2(char * inputString) {
	stack_p1<char> s;
	//if first char isn't A return false
	if (*inputString != 'A')
		return false;

	//gather up A seq
	while (*inputString != '\0') {
		//push A on stack
		if (*inputString == 'A')
			s.push(*inputString);
		else {
			break;
		}
		++inputString;
	}

	//gather up B seq
	while (*inputString != '\0') {
		//if char is B and doesn't exceed amount of A pop from stack
		if (*inputString == 'B' && !s.isEmpty())
			s.pop();
		//(if char other than A or B) or (if B exceeded amount of A) 
		else {
			return false;
		}
		++inputString;
	}
	//return if stack is empty
	return s.isEmpty();
}

bool stacks_for_regular_languages::L3(char *inputString) {
	stack_p1<char> s;
	stack_p1<char> v;

	//if first char isn't A return false
	if (*inputString != 'A') {
		return false;
	}

	//gather up first A seq to determine n
	while (*inputString != '\0') {
		if (*inputString == 'A') {
			s.push(*inputString);
		}
		else {
			break;
		}
		//if chars end after A seq return false
		if(*(inputString + 1) == '\0') { 
			return false;
		}
		++inputString;
	}

	//juggle A and B on different stacks to ensure same length
	while (*inputString != '\0') {
		if(*inputString == 'A') {
			//if B stack isn't empty pop B stack and push A stack
			if(!v.isEmpty()) {
				v.pop();
				s.push(*inputString);
			}

			//if moving on to B without completely finishing A stack return false
			if(*(inputString + 1) == 'B' && !v.isEmpty()) {
					return false;
			}
		} else if(*inputString == 'B') {
			//if A stack isn't empty pop A stack and push B stack
			if(!s.isEmpty()) {
				s.pop();
				v.push(*inputString);

				//if moving on to A without completely finishing B stack return false
				if(*(inputString + 1) == 'A' && !s.isEmpty()) {
					return false;
				}
			//if A stack is empty
			} else {
				return false;
			}
		//if char is anything other than A or B
		} else {
			return false;
		}
		++inputString;
	}
	//return if A stack is empty
	return s.isEmpty();
}                           

bool stacks_for_regular_languages::L4(char *inputString) {
	stack_p1<char> s;
	stack_p1<char> v;
	stack_p1<char> s2;
	stack_p1<char> v2;

	//if first char isn't A return false
	if (*inputString != 'A') {
		return false;
	}
    
	//gather up first A seq to determine n
	while (*inputString != '\0') {
		if (*inputString == 'A') {
			s.push(*inputString);
		}
		else if (*inputString == 'B') {
			break;

		//if char is anything other than A or B
		} else {
			return false;
		}
		//if ending after an A seq
		if(*(inputString + 1) == '\0') { 
			return false;
		}
		++inputString;
	}

	//gather up first B seq to determine m
	while (*inputString != '\0') {
		if (*inputString == 'B') {
			v.push(*inputString);
		} else {
			break;
		}

		//if B seq is end of string return true
		if(*(inputString + 1) == '\0') { 
			return true;
		}
		++inputString;
	}

	while(*inputString != '\0') {
		//keep track of A by juggling between stack s and s2
		if(*inputString == 'A') {
			if(v2.isEmpty()) {
				if(!s.isEmpty()) {
					s.pop();
					s2.push(*inputString);
				} else {
					return false;
				}
			} else if(v.isEmpty()) {
				if(!s2.isEmpty()) {
					s2.pop();
					s.push(*inputString);
				} else {
					return false;
				}
			}

			//(if ending after an A seq) or (if moving on to B seq without completely transfering A stack)
			if( (*(inputString + 1) == 'B' && !s.isEmpty() && !s2.isEmpty()) || (*(inputString + 1) == '\0')) {
				return false;
			}
		//keep track of B by juggling between stack v and v2
		} else if(*inputString == 'B') {
			if(s2.isEmpty()) {
				if(!v2.isEmpty()) {
					v2.pop();
					v.push(*inputString);
				} else {
					return false;
				}
				
			} else if(s.isEmpty()) {
				if(!v.isEmpty()) {
					v.pop();
					v2.push(*inputString);
				} else {
					return false;
				}
			}

			//if moving on to A seq without completely transfering B stack
			if(*(inputString + 1) == 'A' && !v.isEmpty() && !v2.isEmpty()) {
					return false;
			}
		//if letter is anything other than A or B
		} else {
			return false;
		}
		++inputString;
	}

	//if B seq wasn't completely transered by end return false
    if(!v.isEmpty() && !v2.isEmpty()) {
		return false;
	} else {
		return true;
	}
}

#endif 