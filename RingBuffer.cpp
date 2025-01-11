#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

class RingBuffer{
	private:
		vector<int> buffer;
		int size, write_pointer,read_pointer;
		bool is_full;
	public :
		RingBuffer(int size):size(size),write_pointer(0),read_pointer(0),is_full(false){
			buffer.resize(size);}
		void write(int data){
			if(is_full)read_pointer=(read_pointer+1)%size;
			buffer[write_pointer]=data;
			write_pointer=(write_pointer+1)%size;
			is_full=(read_pointer==write_pointer);
		}
		int read(){
			if(is_empty()) throw runtime_error("Buffer is empty");
			int data = buffer[read_pointer];
			read_pointer=(read_pointer+1)%size;
			is_full = false;
			return data;}

	 	bool is_empty() const {
			return !is_full && write_pointer==read_pointer;
		}
};
int main(){
	RingBuffer buffer(5);
	buffer.write(1);
	buffer.write(2);
	buffer.write(3);
	cout << buffer.read() << endl;
	cout << buffer.read() << endl;
	buffer.write(4);
	buffer.write(5);
	buffer.write(6);
	buffer.write(7);
	while(!buffer.is_empty()){
		cout << buffer.read() << endl;
	}
	return 0;
}
