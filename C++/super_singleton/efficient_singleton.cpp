#include <pthread.h>
#include <iostream>

class posix_mutex
{
	public:
	
	posix_mutex()
	{    
		pthread_mutex_lock(&mutex);
	}

	~posix_mutex()
	{
		pthread_mutex_unlock(&mutex);
	}

	pthread_mutex_t mutex;
};

class MySingleton
{
	public: 
		static MySingleton & (*GetInstance)();

		void setI(int n){i = n;}	

		void test()
		{
			std::cout << "test " << i <<  "\n";
		}

	private: 
		static MySingleton * pInstance;

		MySingleton()
		{
		}
	    
		MySingleton(MySingleton &); 
		// force compiler error on copy

		~MySingleton()
		{

		}

		void operator=(MySingleton &); 
		// force compiler error on copy

		static MySingleton & InitialInstance()
		{
			if (!pInstance)
			{
				posix_mutex mutex_lock;
				if (!pInstance) // double check
				{
					// finesse: avoid memory leaks on exit!
					static MySingleton instance;

					pInstance = &instance;
					GetInstance = &RunningInstance;
				}
			}

			return *pInstance;
		}

		static MySingleton & RunningInstance()
		{
			return *pInstance;
		}



	private:
		int i;

};

MySingleton & (*MySingleton::GetInstance)() = &MySingleton::InitialInstance;
MySingleton * MySingleton::pInstance = 0;

int main()
{
	MySingleton & s1 = MySingleton::GetInstance();
	MySingleton & s2 = MySingleton::GetInstance();

	s2.setI( 5 );
	s1.test();
}


