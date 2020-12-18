import matplotlib.pyplot as plt
import numpy as np

#v1 = [0.0052 , 0.0052 , 0.0051 , 0.0051 , 0.0051 , 0.0051 , 0.0051 , 0.0051 , 0.0051 , 0.0051 , 0.0051 , 0.0051 , 0.0051 , 0.0051 , 0.0051 , 0.0076 , 0.0052]
v1 = [0.070802 ,0.091566 ,0.097395 ,0.145875 ,0.203380 ,0.350882 ,0.660904 ,1.176099 ,1.966119 ,3.049818 ,0.214455 ,0.479587 ,1.076414 ,2.111223 ,4.437385 ,10.372136 ,22.342797]
v2 = [0.080802 ,0.191566 ,0.197395 ,0.155875 ,0.233380 ,0.360882 ,0.860904 ,1.176099 ,1.966119 ,3.049818 ,0.214455 ,0.479587 ,1.076414 ,2.111223 ,4.437385 ,10.372136 ,22.342797]
n  = [1 ,2 ,4 ,8 ,16 ,32 ,64 ,128 ,256 ,512 ,1024 ,2048 ,4096 ,8192 ,16384 ,32768 ,65536]

plt.plot(n, v1, color="red", label="Wrapper_Hy_Allreduce")
#plt.plot(n, v2, color="green", label="MPI_Allreduce")
plt.xlabel("Tamaño del mensaje")
plt.ylabel("Tiempo")
plt.legend()
#plt.title("PRUEBAS CON LA MEMORIA CACHE - BUCLES FOR ANIDADOS")
plt.show()

#desviacion = [0.000002 ,0.000040 ,0.000014 ,0.000029 ,0.000001 ,0.000029 ,0.000002 ,0.000044 ,0.000000 ,0.000221 ,0.000391 ,0.000001 ,0.000000 ,0.000001 ,0.000001 ,0.000001 ,0.000001]
desviacion = [0.000047 ,0.000006 ,0.000005 ,0.000495 ,0.000219 ,0.000102 ,0.000097 ,0.000523 ,0.000730 ,0.001232 ,0.000354 ,0.000450 ,0.000465 ,0.000241 ,0.000962 ,0.001139 ,0.002204]
n  = [1 ,2 ,4 ,8 ,16 ,32 ,64 ,128 ,256 ,512 ,1024 ,2048 ,4096 ,8192 ,16384 ,32768 ,65536]

plt.plot(n,desviacion, color="blue", label="Desviación Wrapper_Hy_Allreduce")
plt.xlabel("Tamaño del mensaje")
plt.ylabel("Tiempo")
plt.legend()
#plt.title("PRUEBAS CON LA MEMORIA CACHE - BUCLES FOR ANIDADOS")
#plt.show()