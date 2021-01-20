#!/usr/bin/env python
import time
import serial
import requests
#Serial Communication
try:
    ser = serial.Serial(
          port='/dev/ttyS1',
          baudrate = 9600,
          parity=serial.PARITY_NONE,
          stopbits=serial.STOPBITS_ONE,
          bytesize=serial.EIGHTBITS,
          timeout=1)
    ser2 = serial.Serial(
          port='/dev/ttyS2',
          baudrate = 9600,
          parity=serial.PARITY_NONE,
          stopbits=serial.STOPBITS_ONE,
          bytesize=serial.EIGHTBITS,
          timeout=1)
    ser.flush()
    print("Conexion Serial Exitosa")
    print("Esperando datos....")
    while(True):
      DataRead=ser.readline().strip().decode()
      if(len(DataRead)>0):
        datos = DataRead.split(",")
        temperatura = float(datos[1])
        hr = float(datos[0])
        if(hr>=90):
          if(temperatura>=28):
            print("Frecuencia cardiaca alterada por estres")
            print("Procediendo a encender el aire acondicionado")
            ser2.write('A'.encode())
            ser2.write('\r\n'.encode())
          else:
            print("Frecuencia cardiaca alterada por agente alterno")
            print("Modulando la intensidad de luz")
            ser2.write('I'.encode())
            ser2.write('\r\n'.encode())
        else:
          print("Frecuencia cardiaca estable")
          print("No se realiza ninguna accion en el sistema")
          ser2.write('E'.encode())
          ser2.write('\r\n'.encode())
        print("Enviando datos a thingspeak......")
        enviar = requests.get("https://api.thingspeak.com/update?api_key=P7TDGYXSPPS0S9K8&field1="+str(hr)+"&field2="+str(temperatura))
        if enviar.status_code == requests.codes.ok:
          if enviar.text != '0':
            print("Datos enviados correctamente")
          else:
            print("Tiempo de espera insuficiente (>15seg)")
        else:
          print("Error en el request: ",enviar.status_code)
except(KeyboardInterrupt,SystemExit): #close serial comunication when user force stop
    print()
    print("Gracias por usar nuestro sistema...")
    ser.close()
    ser2.close()
    print("Integrantes:")
    print("- Ronny Benitez")
    print("- Diego Campoverde")
