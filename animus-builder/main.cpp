#include <QCoreApplication>
#include <QTextStream>
#include <QDir>
#include <QFileInfo>

#include "QString"
#include "QFile"
#include "QDir"

void copyDir(QString input, QString output)
{
#ifdef _WIN32
    input.replace("/", "\\");
    system(qPrintable("xcopy \"" + input + "\" \"" + output + "\" /E /H /I /Y"));
#else
    system(("cp -rf " + input + " " + output).c_str());
#endif
}

void copyFile(QString input, QString output)
{
#ifdef _WIN32
    input.replace("/", "\\");
    system(qPrintable("copy /Y \"" + input + "\" \"" + output + "\""));
#else
    system(("yes | cp -rf \"" + input + "\" \"" + output + "\"").c_str());
#endif
}

void setFileAttribute(QString file, QString attr, QString val)
{
    QStringList output;
    QString temp;
    if (!QFileInfo(file).exists())
    {
        return;
    }

    QFile qffile(file);

    QTextStream tstream(&qffile);

    qffile.open(QIODevice::ReadOnly | QIODevice::Text);
    while (true)
    {
        QString line = tstream.readLine();
        if (line.isNull())
            break;
        else
            output.append(line);
    }
    qffile.close();
    qffile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream outstrm(&qffile);
    for (int i = 0; i < output.size(); i++)
    {
        if (output[i].indexOf("#define " + attr) == 0)
        {
            output[i] = "#define " + attr + " " + val;
        }
        outstrm << output[i] + "\n";
    }

    qffile.close();
}

static bool isAlphanumeric(const QString input)
{
    bool output = true;
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i].isLetterOrNumber())
        {
            // do nothing
        }
        else
        {
            output = false;
        }
    }
    return output;
}

static bool isAlphanumericOrSpace(const QString input)
{
    bool output = true;
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i].isLetterOrNumber() || input[i] == ' ')
        {
            // do nothing
        }
        else
        {
            output = false;
        }
    }
    return output;
}





static bool isNumeric(const QString input)
{
    bool output = true;
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i].isDigit())
        {
            // do nothing
        }
        else
        {
            output = false;
        }
    }
    return output;
}

static bool isArray(QString input)
{
    bool output = true;
    input.replace(" ", "");
    QStringList iList = input.split(",");
    foreach (QString ielement, iList)
    {
        if (!isAlphanumeric(ielement))
        {
            output = false;
        }
    }

    return output;
}


static QStringList toStringList(QString input)
{
    if (isArray(input))
    {
        input.replace(" ", "");
        QStringList iList = input.split(",");
        return iList;
    }
}


int main(int argc, char *argv[])
{


    QString animusPath, outputPath, builderRow, builderCol, builderVPins, builderHPins,
            builderRefresh ="10", builderKBName ="Unknown Animus Device", builderKBVariant ="Unknown Animus Device",
            builderKBBuild ="Unknown Animus Variant", modPath,
            modList;

    if (argc < 2)
    {
        QTextStream(stdout) << "Incorrect number of arguments, type \"help\" for more information." << endl;
    }
    else if (argc == 2)
    {
        QString arg1 = argv[1];
        if (arg1 == "help")
        {
            QTextStream(stdout) << "Help menu" << endl
                                << "animusbuilder accepts several argument orders" << endl
                                << "1) animusbuilder [-str animus path] [-str output path] [-int row] [-int col] [-arr<pins> vpins] [-arr<pins> hpins]" << endl <<  endl
                                << "2) animusbuilder [-str animus path] [-str output path] [-int row] [-int col] [-arr<pins> vpins] [-arr<pins> hpins] [-int refresh]" <<  endl <<  endl
                                << "3) animusbuilder [-str animus path] [-str output path] [-int row] [-int col] [-arr<pins> vpins] [-arr<pins> hpins] [-int refresh]" <<  endl <<  endl
                                << "4) animusbuilder [-str animus path] [-str output path] [-int row] [-int col] [-arr<pins> vpins] [-arr<pins> hpins] [-int refresh] [-str kbname] [-str kbvariant] [-str kbdriver build]" <<  endl <<  endl
                                << "5) animusbuilder [-str animus path] [-str output path] [-int row] [-int col] [-arr<pins> vpins] [-arr<pins> hpins] [-int refresh] [-str kbname] [-str kbvariant] [-str kbdriver build] [-str mod path] [-arr<str mod filename>  modlst]" <<  endl <<  endl
                                << "-str denotes a string input such as \"abc\"" <<  endl
                                << "-int denotes an integer input such as 123" <<  endl
                                << "-int denotes an arduino pin input such as 5 or A0" <<  endl
                                << "-arr<t> denotes an array of type t" <<  endl
                                << "arrays are declared without brackets, separated with commas, and surrounded by quotes" <<  endl
                                << "example array -arr<pins>:\"2, 3, A2, A3, A4\"" <<  endl
                                << "example array -arr<str>: \"abc, def, ghi\"" <<  endl;
        }
        else
        {
            QTextStream(stdout) << "Unknown arguments, type \"help\" for more information." << endl;
        }
    }
    else if (argc > 6)
    {
        QFile::copy("C:\\Users\\blahlicus\\Documents\\GitHub\\animus-family\\animus\\animusmaster\\animusmaster.ino", "C:\\Users\\blahlicus\\Documents\\GitHub\\animus-family\\animus\\asdasd\\animusmaster.ino");
        animusPath = argv[1];
        outputPath = argv[2];
        builderRow = argv[3];
        builderCol = argv[4];
        builderVPins = argv[5];
        builderHPins = argv[6];


        QDir animusDir(animusPath);
        if (!animusDir.exists())
        {
            QTextStream(stdout) << "Directory for animus: " << animusDir.absolutePath() << " does not exist." << endl;
            exit(-1);
        }
        QFileInfo animusMain(animusDir.absoluteFilePath(animusDir.dirName() + ".ino"));
        if (!animusMain.exists())
        {
            QTextStream(stdout) << "Main driver file not found for animus: " << animusMain.absoluteFilePath() << endl;
            exit(-1);
        }
        QFileInfo animusMod(animusDir.absoluteFilePath("mod.ino"));
        if (!animusMod.exists())
        {
            QTextStream(stdout) << "mod driver file not found for animus: " << animusMod.absoluteFilePath() << endl;
            exit(-1);
        }
        QDir outputDir(outputPath);
        if (!outputDir.exists())
        {
            outputDir.removeRecursively();
        }

        outputDir.setPath(outputDir.absoluteFilePath(animusDir.dirName()));

        QFileInfo outMain(outputDir.absoluteFilePath(outputDir.dirName() + ".ino"));
        QFileInfo outMod(outputDir.absoluteFilePath("mod.ino"));

        copyDir(animusDir.absolutePath(), outputDir.absolutePath());
        QTextStream(stdout) << "balkjkhasdg" << endl;

        if (!isNumeric(builderRow))
        {
            QTextStream(stdout) << "Row argument not numeric: " << builderRow << endl;
            exit(-1);
        }

        setFileAttribute(outMain.absoluteFilePath(), "builder_row", builderRow);

        if (!isNumeric(builderCol))
        {
            QTextStream(stdout) << "Col argument not numeric: " << builderCol << endl;
            exit(-1);
        }

        setFileAttribute(outMain.absoluteFilePath(), "builder_col", builderCol);

        if (!isArray(builderVPins))
        {
            QTextStream(stdout) << "Vertical pin array argument not valid: " << builderVPins << endl;
            exit(-1);
        }

        setFileAttribute(outMain.absoluteFilePath(), "builder_vpins", builderVPins);

        if (!isArray(builderHPins))
        {
            QTextStream(stdout) << "Horizontal pin array argument not valid: " << builderHPins << endl;
            exit(-1);
        }

        setFileAttribute(outMain.absoluteFilePath(), "builder_hpins", builderHPins);



        if (argc > 7)
        {

            builderRefresh = argv[7];
            if (!isNumeric(builderRefresh))
            {
                QTextStream(stdout) << "Refresh rate argument not numeric: " << builderRefresh << endl;
                exit(-1);
            }

            setFileAttribute(outMain.absoluteFilePath(), "builder_refresh", builderRefresh);

            if (argc > 10)
            {
                builderKBName = argv[8];
                builderKBVariant = argv[9];
                builderKBBuild = argv[10];

                if (!isAlphanumericOrSpace(builderKBName))
                {
                    QTextStream(stdout) << "Keyboard name not alphanumeric or space: " << builderKBName << endl;
                    exit(-1);
                }
                setFileAttribute(outMain.absoluteFilePath(), "builder_kbname", builderKBName);

                if (!isAlphanumericOrSpace(builderKBVariant))
                {
                    QTextStream(stdout) << "Keyboard variant not alphanumeric or space: " << builderKBVariant << endl;
                    exit(-1);
                }
                setFileAttribute(outMain.absoluteFilePath(), "builder_kbvariant", builderKBVariant);

                if (!isAlphanumericOrSpace(builderKBBuild))
                {
                    QTextStream(stdout) << "Keyboard build not alphanumeric or space: " << builderKBBuild << endl;
                    exit(-1);
                }
                setFileAttribute(outMain.absoluteFilePath(), "builder_kbdriver_build", builderKBBuild);


                if (argc > 12)
                {
                    modPath = argv[11];
                    modList = argv[12];

                    if (!isArray(modList))
                    {
                        QTextStream(stdout) << "Mod array not valid: " << modList << endl;
                        exit(-1);

                    }

                    QDir modDir(modPath);
                    if (!modDir.exists())
                    {
                        QTextStream(stdout) << "Directory for mods: " << modDir.absolutePath() << " does not exist." << endl;
                        exit(-1);
                    }

                    QStringList modSList = toStringList(modList);

                    QString builder_mstartup = "";
                    QString builder_mloop = "";
                    QString builder_mkeydown = "";
                    QString builder_mkeyup = "";
                    QString builder_mserial = "";
                    foreach(QString mStr, modSList)
                    {
                        builder_mstartup = builder_mstartup + mStr + "Startup(); ";
                        builder_mloop = builder_mloop + mStr + "Loop(); ";
                        builder_mkeydown = builder_mkeydown + mStr + "KeyDown(val, type); ";
                        builder_mkeyup = builder_mkeyup + mStr + "KeyUp(val, type); ";
                        builder_mserial = builder_mserial + mStr + "Serial(input); ";

                        QFileInfo modStri(modDir.absoluteFilePath("mod_" + mStr + ".ino"));
                        if (!modStri.exists())
                        {
                            QTextStream(stdout) << "File does not exist for mod: " << mStr << endl;
                            exit(-1);
                        }
                        else
                        {
                            QTextStream(stdout) << modDir.absoluteFilePath("mod_" + mStr + ".ino") << endl;
                            copyFile(modDir.absoluteFilePath("mod_" + mStr + ".ino"), outputDir.absoluteFilePath("mod_" + mStr + ".ino"));
                        }
                    }

                    setFileAttribute(outMod.absoluteFilePath(), "builder_mstartup", builder_mstartup);
                    setFileAttribute(outMod.absoluteFilePath(), "builder_mloop", builder_mloop);
                    setFileAttribute(outMod.absoluteFilePath(), "builder_mkeydown", builder_mkeydown);
                    setFileAttribute(outMod.absoluteFilePath(), "builder_mkeyup", builder_mkeyup);
                    setFileAttribute(outMod.absoluteFilePath(), "builder_mserial", builder_mserial);


                }
            }
        }//*/

    }
    return 0;
}
