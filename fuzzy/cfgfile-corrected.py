
inputVar1 = [
    {'lne' : [-100, -8, -4]},
    {'sne' : [-8, -4, 0]},
    {'ze' : [-4, 0, 4]},
    {'spe' : [0, 4, 8]},
    {'lpe' : [4, 8, 100]}
    ]

inputVar2 = [
    {'lnde' : [-10, -0.5, -0.1]},
    {'snde' : [-0.5, -0.1, 0]},
    {'zde' : [-0.1, 0, 0.1]},
    {'spde' : [0, 0.1, 0.5]},
    {'lpde' : [0.1, 0.5, 10]}
    ]

outputVar1 = [1, 2, 3, 4, 5,
              6, 7, 8, 9, 10,
              11, 12, 13, 14, 15,
              16, 17, 18, 19, 20,
              21, 22, 23, 24, 25]

header = "input_vars : 2 \n" + "output_vars : 1 \n\n"
header += "# A/B \nvariant : A \n\n"
header += "# min/product \ntnorm : min \n\n"
header += "# min/product \nimplication : min \n\n"
header += "# COG/COA \ndefuzzification : COG \n\n"
header += "# sum/max/~ \naggregation : sum \n\n"
header += "inputVar1 : e \n"
header += "inputVar2 : de \n"
header += "outputVar1 : ufc \n\n"

#outputVar1MFS = []
kp = 10
ki = 0.115

inputVar1mfs = "inputVar1MFS : \n"
inputVar2mfs = "inputVar2MFS : \n"
outputVar1mfs = "outputVar1MFS : \n"

table1 = "table1 : \n"
i = 1

for a in inputVar2:
    for keyInput2 in a.keys():
        inputVar2mfs += "    - name : " + keyInput2 + "\n"
        inputVar2mfs += "      left : " + str(a[keyInput2][0]) + "\n"
        inputVar2mfs += "      maximum : " + str(a[keyInput2][1]) + "\n"
        inputVar2mfs += "      right : " + str(a[keyInput2][2]) + "\n"

for a in inputVar1:
    for keyInput1 in a.keys():
        inputVar1mfs += "    - name : " + keyInput1 + "\n"
        inputVar1mfs += "      left : " + str(a[keyInput1][0]) + "\n"
        inputVar1mfs += "      maximum : " + str(a[keyInput1][1]) + "\n"
        inputVar1mfs += "      right : " + str(a[keyInput1][2]) + "\n"
        for b in inputVar2:
            for keyInput2 in b.keys():
                #mftemp = kp * b[keyInput2][1] + ki * a[keyInput1][1]
                mftemp = outputVar1[i]
                outputVar1mfs += "    - name : mf" + str(i) + "\n"
                outputVar1mfs += "      value : " + str(mftemp) + "\n"

                #mftemp = outputVar1MFS[i]
                table1 += "    - rule :\n"
                table1 += "        - " + keyInput1 + "\n"
                table1 += "        - " + keyInput2 + "\n"
                table1 += "        - mf" + str(i) + "\n"

                i += 1


with open('cfg-corrected.fzy', 'w') as myfileh:
    myfileh.write(header)
    myfileh.write(inputVar1mfs)
    myfileh.write("\n")
    myfileh.write(inputVar2mfs)
    myfileh.write("\n")
    myfileh.write(outputVar1mfs)
    myfileh.write("\n")
    myfileh.write(table1)
    myfileh.write("\n")
    print "wrote"
