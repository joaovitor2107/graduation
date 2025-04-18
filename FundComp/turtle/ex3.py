import turtle
def triangulo(size, x, y):
    tartaruga.up()
    tartaruga.setpos(x, y)
    tartaruga.fillcolor("red")
    tartaruga.begin_fill()
    tartaruga.forward(size)
    tartaruga.left(120)
    tartaruga.forward(size)
    tartaruga.left(120)
    tartaruga.left(120)
    tartaruga.end_fill()

def retangulo(sizex, sizey, x, y, color):
    tartaruga.up()
    tartaruga.setpos(x, y)
    tartaruga.fillcolor(color)
    tartaruga.begin_fill()
    tartaruga.fd(sizex)
    tartaruga.left(90)
    tartaruga.fd(sizey)
    tartaruga.left(90)
    tartaruga.fd(sizex)
    tartaruga.left(90)
    tartaruga.fd(sizey)
    tartaruga.left(90)
    tartaruga.end_fill()

def paralelogramo(sizex, sizey, x, y):
    tartaruga.up()
    tartaruga.setpos(x, y)
    tartaruga.fillcolor("red")
    tartaruga.begin_fill()
    tartaruga.fd(sizex)
    tartaruga.left(120)
    tartaruga.fd(sizey)
    tartaruga.left(60)
    tartaruga.fd(sizex)
    tartaruga.left(120)
    tartaruga.fd(sizey)
    tartaruga.left(60)
    tartaruga.end_fill()

tartaruga = turtle.Turtle()
tartaruga.shape("turtle")
retangulo(80, 100, 0, 0, "yellow")
retangulo(20, 30, 30, 0, "black")
retangulo(140, 100, 80, 0,"orange")
retangulo(30, 20, 110, 30, "black")
retangulo(30, 20, 170, 30, "black")
paralelogramo(140,80 ,80, 100)
triangulo(80, 0, 100)

