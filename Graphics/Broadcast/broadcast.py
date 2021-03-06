import matplotlib.pyplot as plt
import numpy as np

#v1 = [0.0052 , 0.0052 , 0.0051 , 0.0051 , 0.0051 , 0.0051 , 0.0051 , 0.0051 , 0.0051 , 0.0051 , 0.0051 , 0.0051 , 0.0051 , 0.0051 , 0.0051 , 0.0076 , 0.0052]
v1 = [0.016293 ,0.012116 ,0.014084 ,0.011945 ,0.008165 ,0.009633 ,0.007365 ,0.006924 ,0.008625 ,0.009028 ,0.007571 ,0.007287 ,0.007818 ,0.006870 ,0.007449 ,0.007981 ,0.008551]
v2 = [0.019293 ,0.012316 ,0.134084 ,0.131945 ,0.108165 ,0.019633 ,0.017365 ,0.016424 ,0.017625 ,0.009028 ,0.007571 ,0.007287 ,0.007818 ,0.006870 ,0.007449 ,0.007981 ,0.008551]
n  = [1 ,2 ,4 ,8 ,16 ,32 ,64 ,128 ,256 ,512 ,1024 ,2048 ,4096 ,8192 ,16384 ,32768 ,65536]

plt.plot(n, v1, color="red", label="Wrapper_Hy_Broadcast")
#plt.plot(n, v2, color="green", label="MPI_Broadcast")
plt.xlabel("Tamaño del mensaje")
plt.ylabel("Tiempo")
plt.legend()
#plt.title("PRUEBAS CON LA MEMORIA CACHE - BUCLES FOR ANIDADOS")
plt.show()


desviacion = [0.000001 ,0.000000 ,0.000000 ,0.000000 ,0.000000 ,0.000000 ,0.000000 ,0.000000 ,0.000000 ,0.000000 ,0.000000 ,0.000001 ,0.000000 ,0.000000 ,0.000000 ,0.000000 ,0.000000]
#desviacion = [0.000002 ,0.000001 ,0.000004 ,0.000001 ,0.000002 ,0.000007 ,0.000000 ,0.000000 ,0.000001 ,0.000004 ,0.000001 ,0.000007 ,0.000001 ,0.000001 ,0.000001 ,0.000006 ,0.000002]
n  = [1 ,2 ,4 ,8 ,16 ,32 ,64 ,128 ,256 ,512 ,1024 ,2048 ,4096 ,8192 ,16384 ,32768 ,65536]

plt.plot(n,desviacion, color="blue", label="Desviación Wrapper_Hy_Broadcast")
plt.xlabel("Tamaño del mensaje")
plt.ylabel("Tiempo")
plt.legend()
#plt.title("PRUEBAS CON LA MEMORIA CACHE - BUCLES FOR ANIDADOS")
plt.show()