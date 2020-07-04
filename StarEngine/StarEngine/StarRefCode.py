import os
import platform
import time
try:
   import cPickle as pickle
except:
   import pickle

PointPropertyDic = {}
PropertyDic = {}
Functions = []


class SFunction:
    def __init__(self):
        self.FunctionName = ''
        self.ReturnType = ''
        self.ParmsDic = {}
        self.ParmSequence = []


def ScanFile(directory, prefix=None, postfix=None):
    file_list = []
    for root, sub_dirs, files in os.walk(directory):
        for special_file in files:
            # 如果指定前缀或者后缀
            if postfix or prefix:
                # 同时指定前缀和后缀
                if postfix and prefix:
                    if special_file.endswith(postfix) and special_file.startswith(prefix):
                        file_list.append(os.path.join(root, special_file))
                        continue

                # 只指定后缀
                elif postfix:
                    if special_file.endswith(postfix):
                        file_list.append(os.path.join(root, special_file))
                        continue

                # 只指定前缀
                elif prefix:
                    if special_file.startswith(prefix):
                        file_list.append(os.path.join(root, special_file))
                        continue

            # 前缀后缀均未指定
            else:
                file_list.append(os.path.join(root, special_file))
                continue
    # print(file_list)	 # 打印出扫描到的文件路径
    return file_list


def TimeStampToTime(timestamp):
    timeStruct = time.localtime(timestamp)
    return time.strftime('%Y-%m-%d %H:%M:%S',timeStruct)


def get_FileModifyTime(filePath):
    t = os.path.getmtime(filePath)
    return t


def GetPropertyKeyWord(LineStr):
    PropertyName = ""
    PropertyType = ""
    EqualCount = LineStr.count("=")
    HasEqual = False
    if EqualCount > 0:
        HasEqual = True
    StratGetName = False
    StartGetType = False
    bGeneric = 0
    bEndGeneric = False
    FindPoint = False
    IsPoint = False
    for index in range(len(LineStr)):
        str = LineStr[len(LineStr) - index - 1]
        if HasEqual:
            if str == "=":
                StratGetName = True
        else:
            if str == ";":
                StratGetName = True

        if StratGetName:
            if PropertyName != "" and (str == " "
                                       or str == "	"
                                       or str == "\n"
                                       or str == "*"):
                StratGetName = False
                StartGetType = True
            else:
                if not (str == " "
                        or str == "	"
                        or str == "\n"
                        or str == "*"
                        or str == "&"
                        or str == ";"
                        or str == "="):
                    PropertyName += str

        if StartGetType:
            if str == ">":
                bGeneric += 1
                PropertyType += str
            elif str == "<":
                PropertyType += str
                bGeneric -= 1
                if bGeneric == 0:
                    bEndGeneric = True
            elif bGeneric > 0:
                PropertyType += str
            elif (PropertyType != "" and not bEndGeneric) \
                    and (str == " " or str == "	" or str == "\n")\
                    and not FindPoint:
                break
            elif not (str == " "
                      or str == "	"
                      or str == "\n"
                      or str == "&"
                      or str == ";"
                      or str == "="):
                bEndGeneric = False
                FindPoint = False
                PropertyType += str
                if str == "*":
                    IsPoint = True
                    FindPoint = True
    PropertyName = ''.join(reversed(PropertyName))
    PropertyType = ''.join(reversed(PropertyType))
    if IsPoint:
        PointPropertyDic[PropertyName] = PropertyType
    else:
        PropertyDic[PropertyName] = PropertyType
    return


def GetPropertyFunctionWord(LineStr):
    FunctionName = ""
    ReturnType = ""
    HasRealize = LineStr.count("{")
    ParmDic = {}
    StartGetParm = False
    StratGetName = False
    StartGetReturnType = False
    bGeneric = 0
    FindPoint = False
    bEndGeneric = False
    ParmLine = ""
    ParmRangeCount = 0
    f = SFunction()
    for index in range(len(LineStr)):
        str = LineStr[len(LineStr) - index - 1]
        if HasRealize > 0:
            if str == "{":
                HasRealize -= 1
                if HasRealize == 0:
                    StartGetParm = True
        elif str == ")" and not StartGetParm:
            ParmRangeCount += 1
            StartGetParm = True
            continue
        if StartGetParm:
            if str == ")":
                ParmRangeCount += 1
            elif str == "(":
                ParmRangeCount -= 1
                if ParmRangeCount == 0:
                    StratGetName = True
                    StartGetParm = False
                    # ParmLine = ''.join(reversed(ParmLine))
                    continue
            else:
                ParmLine += str
        if StratGetName:
            if FunctionName != "" and (str == " "
                                       or str == "	"
                                       or str == "\n"):
                StratGetName = False
                StartGetReturnType = True
            else:
                if not (str == " "
                        or str == "	"
                        or str == "\n"
                        or str == "*"
                        or str == "&"
                        or str == ";"
                        or str == "="):
                    FunctionName += str
        if StartGetReturnType:
            if str == ">":
                bGeneric += 1
                ReturnType += str
            elif str == "<":
                ReturnType += str
                bGeneric -= 1
                if bGeneric == 0:
                    bEndGeneric = True
            elif bGeneric > 0:
                ReturnType += str
            elif (ReturnType != "" and not bEndGeneric) \
                    and (str == " " or str == "	" or str == "\n")\
                    and not FindPoint:
                break
            elif not (str == " "
                      or str == "	"
                      or str == "\n"
                      or str == "&"
                      or str == ";"
                      or str == "="):
                bEndGeneric = False
                FindPoint = False
                ReturnType += str
                if str == "*":
                    FindPoint = True
    Parms = ParmLine.split(",")
    for ParmsStr in Parms:
        StratGetParmName = False
        StratGetParmType = False
        ParmName = ""
        ParmType = ""
        bGeneric = 0
        bEndGeneric = False
        FindPoint = False
        FindRef = False
        EqualCount = ParmsStr.count("=")
        for str in ParmsStr:
            if EqualCount > 0:
                if str == "=":
                    StratGetParmName = True
            else:
                if not StratGetParmType:
                    StratGetParmName = True
            if StratGetParmName:
                if ParmName != "" and (str == " "
                                           or str == "	"
                                           or str == "\n"
                                           or str == "*"):
                    StratGetParmName = False
                    StratGetParmType = True
                else:
                    if not (str == " "
                            or str == "	"
                            or str == "\n"
                            or str == "*"
                            or str == "&"
                            or str == ";"
                            or str == "="):
                        ParmName += str
            if StratGetParmType:
                if str == ">":
                    bGeneric += 1
                    ParmType += str
                elif str == "<":
                    ParmType += str
                    bGeneric -= 1
                    if bGeneric == 0:
                        bEndGeneric = True
                elif bGeneric > 0:
                    ParmType += str
                elif (ParmType != "" and not bEndGeneric) \
                        and (str == " " or str == "	" or str == "\n") \
                        and not FindPoint\
                        and not FindRef:
                    break
                elif not (str == " "
                          or str == "	"
                          or str == "\n"
                          or str == ";"
                          or str == "="):
                    bEndGeneric = False
                    FindPoint = False
                    FindRef = False
                    ParmType += str
                    if str == "*":
                        FindPoint = True
                    if str == "&":
                        FindRef = True
        ParmName = ''.join(reversed(ParmName))
        ParmType = ''.join(reversed(ParmType))
        if ParmName != "":
            ParmDic[ParmName] = ParmType
            f.ParmSequence.append(ParmName)
    FunctionName = ''.join(reversed(FunctionName))
    ReturnType = ''.join(reversed(ReturnType))
    f.ParmsDic = ParmDic
    f.FunctionName = FunctionName
    f.ReturnType = ReturnType
    Functions.append(f)
    f.ParmSequence.reverse()
    return


def writeConfigCode(className, lineNum, pointPropertyDic, fileName, Fpath):
    abspath = os.path.abspath('.')
    postfixFileName = Fpath.replace(abspath, "").replace("\\", "_").rstrip(".h").strip("_")
    starcode = "#define "+postfixFileName+"_H_STAR_FILE_DEFINE_CODE_" + str(lineNum) + " \\\n"
    starcode += "virtual void ConfigGCRef(){\\\n"
    for key in pointPropertyDic.keys():
        starcode += "AddGCRef(&" + key + ");\\\n"
    funnum = 0
    for fun in Functions:
        funnum += 1
        starcode += "SFunction fun" + str(funnum) + ";\\\n"
        starcode += "fun"+str(funnum) + ".fun = (BaseSFunction)&"+className+"::exe"+fun.FunctionName+";\\\n"
        starcode += "funRefMap[\""+fun.FunctionName+"\"]=fun"+str(funnum)+";\\\n"
    starcode += "}\\\n"
    funnum = 0
    for fun in Functions:
        funnum += 1
        starcode += fun.ReturnType+" exe" + fun.FunctionName + "(void * obj , ...){\\\n"
        if len(fun.ParmsDic.keys()) > 0:
            starcode += "va_list arglist;\\\n"
            starcode += "va_start(arglist,obj);\\\n"
        # print(fun.FunctionName)
        # print(fun.ReturnType)
        parmNum = 0
        for key in fun.ParmSequence:
            parmNum += 1
            if fun.ParmsDic[key] == "float":
                fun.ParmsDic[key] = "double"
            starcode += fun.ParmsDic[key]+" parm" + str(parmNum) + " = va_arg(arglist," + fun.ParmsDic[key] + ");\\\n"
            # print(key)
            # print(fun.ParmsDic[key])
        starcode += "this->"+fun.FunctionName+"("
        for parmindex in range(1, parmNum+1):
            starcode += "parm"+str(parmindex)
            if parmindex != parmNum:
                starcode += ","
        starcode += ");\\\n"
        if len(fun.ParmsDic.keys()) > 0:
            starcode += "va_end(arglist);\\\n"
        if funnum == len(Functions):
            starcode += "}\n"
        else:
            starcode += "}\\\n"
    starcode += "//"+postfixFileName+"_STAR_DEFINE_CODE_" + str(lineNum)+"_END \n \n"
    # print(starcode)
    if not os.path.exists(os.getcwd()+"\\StarRefCode"):
        os.mkdir(os.getcwd()+"\\StarRefCode")
    if not os.path.exists(os.getcwd()+"\\StarRefCode\\"+fileName+"StarCode.h"):
        wfff = open(os.getcwd()+"\\StarRefCode\\"+fileName+"StarCode.h", "w+")
        wfff.close()
    wf = open(os.getcwd()+"\\StarRefCode\\"+fileName+"StarCode.h", "r+")
    if not wf.read().count("#define CURFILENAMEID " + postfixFileName + "_H_STAR_FILE_DEFINE_CODE_") > 0:
        wf.write("#undef CURFILENAMEID \n")
        wf.write("#define CURFILENAMEID " + postfixFileName + "_H_STAR_FILE_DEFINE_CODE_\n\n")
    tell = wf.tell()
    wf.seek(0)
    isFind = False
    repstr = ""
    for codelinestr in wf.readlines():
        if codelinestr.count("#define "+postfixFileName+"_H_STAR_FILE_DEFINE_CODE_" + str(lineNum) + " \\") > 0:
            isFind = True
        if isFind:
            repstr += codelinestr
        if isFind and codelinestr.count("//"+postfixFileName+"_STAR_DEFINE_CODE_" + str(lineNum)+"_END") > 0:
            break
    if isFind:
        wf.seek(0)
        code = wf.read().replace(repstr, starcode)
        wf.seek(0)
        wf.truncate()
        wf.seek(0)
        wf.write(code)
    else:
        wf.seek(tell)
        wf.write(starcode)
    wf.close()
    return starcode


refcodeMetaData = {}
if not os.path.exists(os.getcwd()+"\\RefCodeData"):
    refcodeData = open(os.getcwd()+"\\RefCodeData", "w")
    refcodeData.close()
if os.path.getsize(os.getcwd()+"\\RefCodeData") > 0:
    refcodeData = open(os.getcwd()+"\\RefCodeData", "rb+")
    refcodeMetaData = pickle.load(refcodeData)
else:
    refcodeMetaData = {}
Fpathlist = ScanFile(os.getcwd()+"\\Source", postfix=".h")
for Fpath in Fpathlist:
    FileName = os.path.splitext(os.path.split(Fpath)[1])[0]
    lastchangetime = os.stat(Fpath).st_mtime
    file_object = open(Fpath, "r", encoding='utf-8')
    if FileName == "Define":
        continue
    if file_object.read().count("SCLASS") > 0:
        if Fpath in refcodeMetaData.keys():
            if refcodeMetaData[Fpath] != lastchangetime:
                refcodeMetaData[Fpath] = os.stat(Fpath).st_mtime
            else:
                continue
        else:
            refcodeMetaData[Fpath] = os.stat(Fpath).st_mtime
    file_object.seek(0)
    IsSPROPERTY = 0
    IsSFUNCTION = 0
    IsSCLASS = 0
    LineNum = 0
    starcode = ""
    curClassName = ""
    lastClassName = ""
    lastDefineLineNum = -1

    for line in file_object.readlines():
        LineNum += 1
        line = line.strip()
        if len(line) >= 2 and line[0] == "/" and line[1] == "/":
            IsSPROPERTY = 0
            IsSFUNCTION = 0
            IsSCLASS = 0
            continue
        if IsSCLASS > 0:
            lastClassName = curClassName
            curClassName = ""
            classstrindex = line.find("class") + 5
            for index in range(classstrindex, len(line)):
                if curClassName != "" and (line[index] == " "
                                           or line[index] == ":"
                                           or line[index] == "	"
                                           or line[index] == ";"
                                           or line[index] == "="):
                    break
                else:
                    curClassName += line[index]
        if line.count("STAR_DEFINE_CODE") > 0:
            if lastDefineLineNum == -1:
                lastDefineLineNum = LineNum
                continue
            if lastDefineLineNum != -1:
                writeConfigCode(lastClassName, lastDefineLineNum, PointPropertyDic, FileName, Fpath)
            lastDefineLineNum = LineNum
            PointPropertyDic = {}
            PropertyDic = {}
            Functions = []
            continue
        if IsSPROPERTY > 0:
            GetPropertyKeyWord(line)
        if IsSFUNCTION > 0:
            GetPropertyFunctionWord(line)
        IsSPROPERTY = line.count("SPROPERTY")
        IsSFUNCTION = line.count("SFUNCTION")
        IsSCLASS = line.count("SCLASS")
    if lastDefineLineNum != -1:
        writeConfigCode(curClassName, lastDefineLineNum, PointPropertyDic, FileName, Fpath)
    PointPropertyDic = {}
    PropertyDic = {}
    Functions = []
    file_object.close()
if os.path.getsize(os.getcwd()+"\\RefCodeData") > 0:
    refcodeData.close()
refcodeData = open(os.getcwd()+"\\RefCodeData", "wb")
pickle.dump(refcodeMetaData, refcodeData)
refcodeData.close()
