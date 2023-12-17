// Code your design here.
// Uncomment the next line for SystemC modules.
// #include <systemc>
// Code your design here
#include <systemc.h>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include <ctime>


using namespace sc_core;
using namespace std;


/*
export SYSTEMC_HOME=/usr/local/systemc-2.3.3
export CXX=g++
g++ -I. -I$SYSTEMC_HOME/include -L. -L$SYSTEMC_HOME/lib-linux64 -Wl,-rpath=$SYSTEMC_HOME/lib-linux64 -o test Double_door_systemc.cpp -lsystemc -lm
./test
*/

// lưu giá trị của các sensors
class DoorSensor
{
private:
    bool pir1, pir2; // input
    bool door_state;
public:
    DoorSensor(){};
    DoorSensor(bool pir1, bool pir2, bool door_state)
    {
        this->pir1 = pir1;
        this->pir2 = pir2;
        this->door_state = door_state;
    }

    void set_PIR1(bool pir1)
    {
        this->pir1 = pir1;
    }

    void set_PIR2(bool pir2)
    {
        this->pir2 = pir2;
    }

    void set_door_state(bool door_state)
    {
        this->door_state = door_state;
    }

    bool get_PIR1()
    {
        return this->pir1;
    }

    bool get_PIR2()
    {
        return this->pir2;
    }
    
    bool get_door_state(){
        return this->door_state;
    }
};

SC_MODULE (DOOR_System) {
// Các khai báo các thành phần của module
  sc_in<bool> pirA1;
  sc_in<bool> pirA2;
  sc_in<bool> pirB1;
  sc_in<bool> pirB2;
  sc_out<bool> door_stateA, door_stateB;

  DoorSensor doorA, doorB;
// Phương thức xử lý sự kiện
  void control_logic() {
    
    doorA = DoorSensor(0,0,0); 
    doorB = DoorSensor(0,0,0);
  
  for (int i = 0; i< 20;i++){
   //case 1
    if (i==0) doorA.set_PIR1(1);
    else if (i==1) doorA.set_PIR1(0);
    else if (i==2) doorB.set_PIR2(1);
    else if (i==3) doorB.set_PIR2(0);
    

   //case 2
    else if (i==5) doorB.set_PIR1(1);
    else if (i==6) {doorB.set_PIR1(0);}
    else if (i==7) doorA.set_PIR2(1);
    else if (i==8) doorA.set_PIR2(0);
    


    //case 3
    else if (i==10) doorA.set_PIR1(1);
    else if (i==11) {doorB.set_PIR2(1);}
    else if (i==12) doorA.set_PIR1(0);
    else if (i==13) doorB.set_PIR2(0);

    //case 4
    else if (i==15) doorA.set_PIR1(1);
    else if (i==16) doorA.set_PIR1(0);
    else if (i==17) doorA.set_PIR2(1);
    else if (i==18) doorA.set_PIR2(0);
   
	if (doorA.get_door_state() == 0 && doorB.get_door_state() == 0){
      cout << sc_time_stamp()<<"	Khong mo ca hai cua"<<endl;	
	wait(5,SC_SEC);
		if (doorA.get_PIR1() == 1 || doorA.get_PIR2() ==  1){
			doorA.set_door_state(1);
			doorB.set_door_state(0);
			//cout << sc_time_stamp()<<"	Cua mot mo, cua hai dong"<<endl;
          
		} else if (doorB.get_PIR2() == 1 || doorB.get_PIR1() == 1){
			doorA.set_door_state(0);
			doorB.set_door_state(1);
			//cout << sc_time_stamp()<<"	Mo cua hai, dong cua mot"<<endl;		            
        }
        else {
			doorA.set_door_state(0);
			doorB.set_door_state(0);
			//cout << sc_time_stamp()<<"	Khong mo ca hai cua"<<endl;			
		}
	} else if (doorA.get_door_state() == 1 && doorB.get_door_state() == 0){
      cout << sc_time_stamp()<<"	Mo cua mot dong cua hai"<<endl;			
	wait(5,SC_SEC);
		if (doorA.get_PIR1() == 0 && doorB.get_PIR2() == 0){
			doorA.set_door_state(0);
			doorB.set_door_state(0);
			//cout << sc_time_stamp()<<"	Khong mo"<<endl;
          
		} else if (doorA.get_PIR1() == 0 && doorB.get_PIR2() == 1){
			doorA.set_door_state(0);
			doorB.set_door_state(1);
			//cout << sc_time_stamp()<<"	Mo cua hai, dong cua mot"<<endl;			
          
		} else if (doorA.get_PIR1() == 1 && doorB.get_PIR2() == 1){
			doorA.set_door_state(1);
			doorB.set_door_state(1);	
			//cout << sc_time_stamp()<<"	Mo ca hai cua"<<endl;			

		} else if (doorA.get_PIR1() == 1 && doorB.get_PIR2() == 0){
			doorA.set_door_state(1);
			doorB.set_door_state(0);
			//cout << sc_time_stamp()<<"	Mo cua mot dong cua hai"<<endl;			

		}
         else if (doorA.get_PIR2() == 0){
			doorA.set_door_state(0);
			doorB.set_door_state(0);
		//	cout << sc_time_stamp()<<"	Khong mo"<<endl;
        } else {
            doorA.set_door_state(1);
			doorB.set_door_state(0);
		//	cout << sc_time_stamp()<<"	Mo cua mot dong cua hai"<<endl;
        }
	} else if (doorA.get_door_state() == 0 && doorB.get_door_state() == 1){
      cout << sc_time_stamp()<<"	Mo cua hai, dong cua mot"<<endl;
	wait(5,SC_SEC);
		if (doorB.get_PIR2() == 0){
			doorA.set_door_state(0);
			doorB.set_door_state(0);
			//cout << sc_time_stamp()<<"	Khong mo"<<endl;			

		} else {
			doorA.set_door_state(0);
			doorB.set_door_state(1);
			//cout << sc_time_stamp()<<"	Mo cua hai, dong cua mot"<<endl;			
          
		}
        if (doorA.get_PIR2() == 1 && doorB.get_PIR1() == 0){
			doorA.set_door_state(1);
			doorB.set_door_state(0);
			//cout << sc_time_stamp()<<"	Mo cua mot dong cua hai"<<endl;	

        } else if (doorA.get_PIR2() == 0 && doorB.get_PIR1() == 0){
			doorA.set_door_state(0);
			doorB.set_door_state(0);
			//cout << sc_time_stamp()<<"	Khong mo"<<endl;

        } else if (doorA.get_PIR2() == 1 && doorB.get_PIR1() == 1){
			doorA.set_door_state(1);
			doorB.set_door_state(1);	
			//cout << sc_time_stamp()<<"	Mo ca hai cua"<<endl;	            
        } else {
			doorA.set_door_state(0);
			doorB.set_door_state(1);	
			//cout << sc_time_stamp()<<"	Mo cua hai dong cua mot"<<endl;	            
        }
	} else {
      cout << sc_time_stamp()<<"	Mo ca hai cua"<<endl;	
	wait(5,SC_SEC);
	
		if (doorA.get_PIR1() ==  1 ){
			doorA.set_door_state(1);
			doorB.set_door_state(1);
           // cout << sc_time_stamp()<<"	Mo ca hai cua"<<endl;
          
		} else if (doorA.get_PIR1() == 0) {
			doorA.set_door_state(0);
			doorB.set_door_state(1);
          	//cout << sc_time_stamp()<<"	Mo cua hai dong cua mot"<<endl;
		}
        else if (doorB.get_PIR1() == 1){
			doorA.set_door_state(1);
			doorB.set_door_state(1);
          //  cout << sc_time_stamp()<<"	Mo ca hai cua"<<endl;            
        } else if (doorB.get_PIR1() == 0){
			doorA.set_door_state(1);
			doorB.set_door_state(0);
          //	cout << sc_time_stamp()<<"	Mo cua mot dong cua hai"<<endl;           
        }
	}
  }
}
// Constructor của module
  SC_CTOR (DOOR_System) {
    // Đăng ký các quá trình hoặc các phương thức xử lý sự kiện
    SC_THREAD (control_logic);
    sensitive << pirA1 << pirA2 << pirB1 << pirB2;
  }
};

int sc_main(int argc, char* argv[]) {
  sc_signal<bool> pirA1, pirA2, pirB1, pirB2;
  sc_signal<bool> door_A, door_B;
  // Tạo một instance của module
  DOOR_System door_system("DOOR_System");
  door_system.pirA1(pirA1);
  door_system.pirA2(pirA2);
  door_system.door_stateA(door_A);
  door_system.pirB1(pirB1);
  door_system.pirB2(pirB2);
  door_system.door_stateB(door_B);
  
  cout << "\n \t HE THONG CUA HAI LOP TU DONG \n\n"<< endl;
  
 // Chạy mô phỏng SystemC
  sc_start();
  return 0;
}
