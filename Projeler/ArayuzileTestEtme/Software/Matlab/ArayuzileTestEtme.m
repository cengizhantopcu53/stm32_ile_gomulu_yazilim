clc
clear all
 
s = serialport('COM5',9600)
writeline(s,"1")
readline(s)

writeline(s,"0")
readline(s)


