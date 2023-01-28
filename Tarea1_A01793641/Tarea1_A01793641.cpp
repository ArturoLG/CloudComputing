
#include <iostream>
#include <omp.h>
//Include omp.h library 
#ifdef _OPENMP
	#include <omp.h>
#else
	#define omp_get_thread_num() 0
#endif

//variables for # of array elements, print elements.
#define N 500
#define chunk 3
#define mostrar 20

//define array print function
void imprimeArreglo(float* d);

int main()
{
	//create 3 arrays of predefined length
	std::cout << "Sumando arreglos en paralelo!\n";
	float a[N], b[N], c[N];
	int i;

	//fill arrays with specified numbers and operations
	for (i = 0; i < N; i++)
	{
		a[i] = i * 10;
		b[i] = (i + 3) * 3.7;
	}

	//define # of elements to chunk for parallel processing
	int pedazos = chunk;

	//The omp parallel directive explicitly instructs the compiler to parallelize the chosen block of code.
	//Shared - Declares the scope of the comma-separated data variables in list to be shared across all threads.
	//Private - Declares the scope of the data variables in list to be private to each thread. Data variables in list are separated by commas.
	//schedule- Defines # of chunks 
	#pragma omp parallel for \
	shared(a,b,c,pedazos) private(i) \
	schedule(static, pedazos)
	for (i = 0; i < N; i++)
		c[i] = a[i] + b[i];

	//print initial configurations, Number of elements in array, chunk, print
	std::cout << "# de elementos en cada arreglo: " << N << std::endl;
	std::cout << "# de pedazos para particionar procesamiento: " << chunk << std::endl;
	std::cout << "# de elementos a mostrar: " << mostrar << std::endl;
	std::cout << "\n\n" << std::endl;

	//print array a elements
	std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << std::endl;
	imprimeArreglo(a);

	//print array b elements
	std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << std::endl;
	imprimeArreglo(b);

	//print array c=a+b elements
	std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c: " << std::endl;
	imprimeArreglo(c);

}

//function used to print arrays
void imprimeArreglo(float* d)
{
	for (int x = 0; x < mostrar; x++)
		std::cout << d[x] << " - ";
	std::cout << std::endl;
}