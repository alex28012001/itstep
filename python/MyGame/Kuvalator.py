from tkinter import *
from math import *



class Per():
    first=0.0
    second=0.0
    otv=0
    second_active=False
    op=" "
    last_value=0
    tochka = 0
    kol_tochka=0


#кнопки чисел
class Buttons_numbers():

    def __init__(self,text,Row,Column,Value):
        self.but = Button(root,
                          text=text,
                          width=6,
                          height=2)


        self.value = int(Value)
        self.but.bind("<Button-1>",self.press)

        self.but.grid(row=Row, column=Column)



    #функция нажатия на кнопку числа
    def press(self, event):
        if Per.second_active==False:

            Per.first =float(Per.first*10+self.value)
            tex.insert(END, self.value)
            Per.last_value=self.value

        else:
            Per.second = float(Per.second * 10 + self.value)
            tex.insert(END, self.value)

class Buttons_operations():

    def __init__(self, Text, Row, Column):
        if Text != "=":
            self.but = Button(root,
                                text=Text,
                                width=6,
                                height=2)
        else:
            self.but = Button(root,
                                text=Text,
                                width=41,
                                height=2,
                                )
        self.text = Text
        self.but.bind("<Button-1>", self.press)
        if Text != "=":
            self.but.grid(row=Row, column=Column)
        else:
            self.but.grid(row=6, column=0, columnspan=7)

    def press(self, event):

        if self.text == "+":
            Per.op = "+"
            Per.second_active = True
            tex.insert(END, self.text)


        if self.text == "-":
            Per.op = "-"
            Per.second_active = True
            tex.insert(END, self.text)


        if self.text == "/":
            Per.op = "/"
            Per.second_active = True
            tex.insert(END, self.text)


        if self.text == "*":
            Per.op = "*"
            Per.second_active = True
            tex.insert(END, self.text)


        if self.text == "%":
            Per.op = "%"
            Per.second_active = True
            tex.insert(END, self.text)



        #нажатие равно
        if self.text == "=":
            tex.insert(END, "=")
            if Per.op=="+":
                tex.insert(END,float(float(Per.first)+float(Per.second)))

            if Per.op == "-":
                tex.insert(END, float(float(Per.first) - float(Per.second)))

            if Per.op == "/":
                tex.insert(END, float(float(Per.first) / float(Per.second)))

            if Per.op == "*":
                tex.insert(END, float(float(Per.first) * float(Per.second)))
            if Per.op == "%":
                tex.insert(END, float(float(Per.first) %  float(Per.second)))
            #print(Per.second, Per.first) -на случай , если будут проблемы с вычеслениями - расскоментить



#main
root=Tk()
root.title("Calculator")


lab=Label(root,text="   Шизометр",font="15").grid(row=0, column=0,columnspan=6)
tex = Entry(root,width=48)

but_plus = Buttons_operations("+", 2, 5)
but_proc = Buttons_operations("%", 2, 6)
but_min = Buttons_operations("-", 3, 5)
but_drob = Buttons_operations("1/x", 3, 6)
but_mnozh = Buttons_operations("*", 4, 5)
but_step = Buttons_operations("x^y", 4, 6)
but_del = Buttons_operations("/", 5, 5)
but_kor = Buttons_operations("√", 5, 6)
but_ravn = Buttons_operations("=",6,0)


but1 = Buttons_numbers("1", 2, 0, 1)
but2 = Buttons_numbers("2", 2, 1, 2)
but3 = Buttons_numbers("3", 2, 2, 3)
but4 = Buttons_numbers("4", 3, 0, 4)
but5 = Buttons_numbers("5", 3, 1, 5)
but6 = Buttons_numbers("6", 3, 2, 6)
but7 = Buttons_numbers("7", 4, 0, 7)
but8 = Buttons_numbers("8", 4, 1, 8)
but9 = Buttons_numbers("9", 4, 2, 9)
but_toch = Buttons_operations(".", 5, 0)
but0 = Buttons_numbers("0", 5, 1, 0)
but_delete = Buttons_operations("←", 5, 2)


tex.grid(row=1, column=0,columnspan=7)
root.mainloop()
