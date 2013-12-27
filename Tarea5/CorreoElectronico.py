 #-*- encoding: utf-8 -*-
 
import serial
import time
import smtplib
 
USUARIO_GMAIL = 'javi9rl@gmail.com'
CONTRASENA_GMAIL = 'Ja26_vi06'
 
DESTINATARIO = 'javi9rl@gmail.com'
REMITENTE = 'javi9rl@gmail.com'
 
ASUNTO  = ' ¡ Temperatura en su casa ! '
MENSAJE =  ' La temperatura es '
 
arduino = serial.Serial('COM7', 9600, timeout = 3.0)   


def enviar_correo_electronico(dato):
    print("Envíando e-mail")
    smtpserver = smtplib.SMTP("smtp.gmail.com",587)     #Definimos el objeto 'smtpserver' con smptlib.SMTP, SMTP("",) Administra la conexión SMTP
    smtpserver.ehlo()                                   #Este método prepara envíar un correo electrónico
    smtpserver.starttls()                               #Pone la conexión con el servidor SMTP en el modo de TLS.
    smtpserver.ehlo()
    smtpserver.login(USUARIO_GMAIL, CONTRASENA_GMAIL)   #Iniciamos sesion en el SMTP server de Google
    header  = 'To:      ' + DESTINATARIO + '\n'         #Construimos el 'HEADER' para envíar el correo electrónico       
    header += 'From:    ' + REMITENTE    + '\n'
    header += 'Subject: ' + ASUNTO       + '\n'
    print header
    msg = header + '\n' + MENSAJE + dato + ' \n\n'             #Concatenamos el'HEADER' y el 'MENSAJE' del correo electrónico
    smtpserver.sendmail(REMITENTE, DESTINATARIO, msg)   #Envíamos el correo electrónico
    smtpserver.close()                                  #Cerramos la conexión con el SMTP server de Google
	
	
while True:
	datoTemp = arduino.readline()	
	lineaLeida = arduino.readline()					   
	print(lineaLeida) 
	if len(lineaLeida)>0 :
		if lineaLeida[0] == 'M' :                       
			enviar_correo_electronico(datoTemp)                     
	time.sleep(0.5)                                     
# EOF