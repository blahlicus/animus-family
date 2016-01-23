#include <QCoreApplication>
#include <QTextStream>
#include <QDir>
#include <QFileInfo>

#include "QString"
#include "QFile"
#include "QDir"

bool copyDir(QString from_dir, QString to_dir, bool replace_on_conflit)
{
    QDir dir;
    dir.setPath(from_dir);

    from_dir += QDir::separator();
    to_dir += QDir::separator();

    foreach (QString copy_file, dir.entryList(QDir::Files))
    {
        QString from = from_dir + copy_file;
        QString to = to_dir + copy_file;

        if (QFile::exists(to))
        {
            if (replace_on_conflit)
            {
                if (QFile::remove(to) == false)
                {
                    return false;
                }
            }
            else
            {
                continue;
            }
        }

        if (QFile::copy(from, to) == false)
        {
            return false;
        }
    }

    foreach (QString copy_dir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        QString from = from_dir + copy_dir;
        QString to = to_dir + copy_dir;

        if (dir.mkpath(to) == false)
        {
            return false;
        }

        if (copyDir(from, to, replace_on_conflit) == false)
        {
            return false;
        }
    }

    return true;
}


int main(int argc, char *argv[])
{


    QString animusPath, outputPath, builderRow, builderCol, builderVPins, builderHPins,
            builderRefresh, builderKBName, builderKBVariant, builderKBBuild, modPath,
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
            QTextStream(stdout) << "Main driver file not found for animus: " << animusMod.absoluteFilePath() << endl;
            exit(-1);
        }
        QDir outputDir(outputPath);
        if (!outputDir.exists())
        {
            outputDir.removeRecursively();
        }

        copyDir(animusDir.absolutePath(), outputDir.absolutePath(), true);


    }
    return 0;
}
