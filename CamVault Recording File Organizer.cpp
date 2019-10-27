#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>

/** Usage: It will create a data.txt file with all your video file names in each line. The files needs to be named in CamVault's format: C4_"camgirl_nickname"_"Month"-"day"-"year"_"hour"-"minute"-"second".mp4
 * This program natively works with Cam4's recordings, but it should work fine with Chaturbate's or MyFreeCams' recordings too, provided you modify in this source code changing "C4_" to "CB_" to work with Chaturbate, or to "MFC_" to work with MyFreeCams.
 */

int findMonth(std::string file)
{
    if (file.find("_January-") != -1)
        return file.find("_January-");
    if (file.find("_February-") != -1)
        return file.find("_February-");
    if (file.find("_March-") != -1)
        return file.find("_March-");
    if (file.find("_April-") != -1)
        return file.find("_April-");
    if (file.find("_May-") != -1)
        return file.find("_May-");
    if (file.find("_June-") != -1)
        return file.find("_June-");
    if (file.find("_July-") != -1)
        return file.find("_July-");
    if (file.find("_August-") != -1)
        return file.find("_August-");
    if (file.find("_September-") != -1)
        return file.find("_September-");
    if (file.find("_October-") != -1)
        return file.find("_October-");
    if (file.find("_November-") != -1)
        return file.find("_November-");
    return file.find("_December-");
}

void fixPath(std::string path)
{
    int i = 0, j = 0, k = 0;
    std::string temp1 = std::string();
    std::string temp2 = std::string();
    std::string temp3 = std::string();
    for (i = 0; i < path.size(); i++)
    {
        if (path[i] == '\\')
            j = i;
        if (path[i] == ' ')
        {
            k = path.find('\\',i);
            temp1 = path.substr(0,j);
            temp1 += "\"";
            temp2 = path.substr(j,k-1);
            temp2 += "\"";
            temp3 = path.substr(k,path.size());
            path.erase(path.begin(),path.end());
            path += temp1 + temp2 + temp3;
            i +=2;
            i = path.find('\"',i);
            temp1.erase(temp1.begin(),temp1.end());
            temp2.erase(temp2.begin(),temp2.end());
            temp3.erase(temp3.begin(),temp3.end());
        }
    }
}

int main(int argc, char *argv[])
{
    int i = 0, j = 0;
    std::string param = std::string();
    std::string video = std::string();
    std::string folder = std::string();
    std::string newFolder = std::string();
    std::string nameOfNewFolder = std::string();

    folder.erase(folder.begin(),folder.end());
    folder.append(argv[0]);
    fixPath(folder);
	i = folder.rfind('\\');
    folder.erase(folder.begin()+i+1,folder.end());

    system("dir > data.txt");
    std::ifstream cam;
    cam.open("data.txt", std::ios::out);

    while(!cam.fail())
    {
        video.erase(video.begin(),video.end());
        getline(cam,video);
        while (video.find("C4_") == -1 && !cam.fail())
        {
            video.erase(video.begin(),video.end());
            getline(cam,video);
        }
        if (cam.fail())
            break;
        i = video.find("C4_");
        video.erase(video.begin(),video.begin()+i-1);

        nameOfNewFolder.erase(nameOfNewFolder.begin(),nameOfNewFolder.end());
        i = video.find("C4_");
        j = findMonth(video);
        if (j == -1)
            break;
        i += 3;
        j -= i;
        nameOfNewFolder = video.substr(i,j);

        newFolder.erase(newFolder.begin(),newFolder.end());
        newFolder = folder.substr(0,folder.size());
        newFolder += nameOfNewFolder;

        param.erase(param.begin(),param.end());
        param += "mkdir " + nameOfNewFolder + " 2>NUL";
        system(param.c_str());
        param.erase(param.begin(),param.end());
        param += "move " + video + " " + nameOfNewFolder + " >NUL";
        system(param.c_str());
    }

    cam.close();
    system("del data.txt");
    return 0;
}
