#include "FastBin.h"

QString FastBin::topy(QString qsChinese){
    QByteArray ba = qsChinese.toLocal8Bit();
    const char* strChs = ba.data();
    static int li_SecPosValue[] = {
       1601, 1637, 1833, 2078, 2274, 2302, 2433, 2594, 2787, 3106, 3212,
       3472, 3635, 3722, 3730, 3858, 4027, 4086, 4390, 4558, 4684, 4925, 5249
      };
      static char* lc_FirstLetter[] = {
       "A", "B", "C", "D", "E", "F", "G", "H", "J", "K", "L", "M", "N", "O",
       "P", "Q", "R", "S", "T", "W", "X", "Y", "Z"
      };
      static char* ls_SecondSecTable =
       "CJWGNSPGCGNE[Y[BTYYZDXYKYGT[JNNJQMBSGZSCYJSYY[PGKBZGY[YWJKGKLJYWKPJQHY[W[DZLSGMRYPYWWCCKZNKYYGTTNJJNYKKZYTCJNMCYLQLYPYQFQRPZSLWBTGKJFYXJWZLTBNCXJJJJTXDTTSQZYCDXXHGCK[PHFFSS[YBGXLPPBYLL[HLXS[ZM[JHSOJNGHDZQYKLGJHSGQZHXQGKEZZWYSCSCJXYEYXADZPMDSSMZJZQJYZC[J[WQJBYZPXGZNZCPWHKXHQKMWFBPBYDTJZZKQHY"
       "LYGXFPTYJYYZPSZLFCHMQSHGMXXSXJ[[DCSBBQBEFSJYHXWGZKPYLQBGLDLCCTNMAYDDKSSNGYCSGXLYZAYBNPTSDKDYLHGYMYLCXPY[JNDQJWXQXFYYFJLEJPZRXCCQWQQSBNKYMGPLBMJRQCFLNYMYQMSQYRBCJTHZTQFRXQHXMJJCJLXQGJMSHZKBSWYEMYLTXFSYDSWLYCJQXSJNQBSCTYHBFTDCYZDJWYGHQFRXWCKQKXEBPTLPXJZSRMEBWHJLBJSLYYSMDXLCLQKXLHXJRZJMFQHXHWY"
       "WSBHTRXXGLHQHFNM[YKLDYXZPYLGG[MTCFPAJJZYLJTYANJGBJPLQGDZYQYAXBKYSECJSZNSLYZHSXLZCGHPXZHZNYTDSBCJKDLZAYFMYDLEBBGQYZKXGLDNDNYSKJSHDLYXBCGHXYPKDJMMZNGMMCLGWZSZXZJFZNMLZZTHCSYDBDLLSCDDNLKJYKJSYCJLKWHQASDKNHCSGANHDAASHTCPLCPQYBSDMPJLPZJOQLCDHJJYSPRCHN[NNLHLYYQYHWZPTCZGWWMZFFJQQQQYXACLBHKDJXDGMMY"
       "DJXZLLSYGXGKJRYWZWYCLZMSSJZLDBYD[FCXYHLXCHYZJQ[[QAGMNYXPFRKSSBJLYXYSYGLNSCMHZWWMNZJJLXXHCHSY[[TTXRYCYXBYHCSMXJSZNPWGPXXTAYBGAJCXLY[DCCWZOCWKCCSBNHCPDYZNFCYYTYCKXKYBSQKKYTQQXFCWCHCYKELZQBSQYJQCCLMTHSYWHMKTLKJLYCXWHEQQHTQH[PQ[QSCFYMNDMGBWHWLGSLLYSDLMLXPTHMJHWLJZYHZJXHTXJLHXRSWLWZJCBXMHZQXSDZP"
       "MGFCSGLSXYMJSHXPJXWMYQKSMYPLRTHBXFTPMHYXLCHLHLZYLXGSSSSTCLSLDCLRPBHZHXYYFHB[GDMYCNQQWLQHJJ[YWJZYEJJDHPBLQXTQKWHLCHQXAGTLXLJXMSL[HTZKZJECXJCJNMFBY[SFYWYBJZGNYSDZSQYRSLJPCLPWXSDWEJBJCBCNAYTWGMPAPCLYQPCLZXSBNMSGGFNZJJBZSFZYNDXHPLQKZCZWALSBCCJX[YZGWKYPSGXFZFCDKHJGXDLQFSGDSLQWZKXTMHSBGZMJZRGLYJB"
       "PMLMSXLZJQQHZYJCZYDJWBMYKLDDPMJEGXYHYLXHLQYQHKYCWCJMYYXNATJHYCCXZPCQLBZWWYTWBQCMLPMYRJCCCXFPZNZZLJPLXXYZTZLGDLDCKLYRZZGQTGJHHGJLJAXFGFJZSLCFDQZLCLGJDJCSNZLLJPJQDCCLCJXMYZFTSXGCGSBRZXJQQCTZHGYQTJQQLZXJYLYLBCYAMCSTYLPDJBYREGKLZYZHLYSZQLZNWCZCLLWJQJJJKDGJZOLBBZPPGLGHTGZXYGHZMYCNQSYCYHBHGXKAMTX"
       "YXNBSKYZZGJZLQJDFCJXDYGJQJJPMGWGJJJPKQSBGBMMCJSSCLPQPDXCDYYKY[CJDDYYGYWRHJRTGZNYQLDKLJSZZGZQZJGDYKSHPZMTLCPWNJAFYZDJCNMWESCYGLBTZCGMSSLLYXQSXSBSJSBBSGGHFJLYPMZJNLYYWDQSHZXTYYWHMZYHYWDBXBTLMSYYYFSXJC[DXXLHJHF[SXZQHFZMZCZTQCXZXRTTDJHNNYZQQMNQDMMG[YDXMJGDHCDYZBFFALLZTDLTFXMXQZDNGWQDBDCZJDXBZGS"
       "QQDDJCMBKZFFXMKDMDSYYSZCMLJDSYNSBRSKMKMPCKLGDBQTFZSWTFGGLYPLLJZHGJ[GYPZLTCSMCNBTJBQFKTHBYZGKPBBYMTDSSXTBNPDKLEYCJNYDDYKZDDHQHSDZSCTARLLTKZLGECLLKJLQJAQNBDKKGHPJTZQKSECSHALQFMMGJNLYJBBTMLYZXDCJPLDLPCQDHZYCBZSCZBZMSLJFLKRZJSNFRGJHXPDHYJYBZGDLQCSEZGXLBLGYXTWMABCHECMWYJYZLLJJYHLG[DJLSLYGKDZPZXJ"
       "YYZLWCXSZFGWYYDLYHCLJSCMBJHBLYZLYCBLYDPDQYSXQZBYTDKYXJY[CNRJMPDJGKLCLJBCTBJDDBBLBLCZQRPPXJCJLZCSHLTOLJNMDDDLNGKAQHQHJGYKHEZNMSHRP[QQJCHGMFPRXHJGDYCHGHLYRZQLCYQJNZSQTKQJYMSZSWLCFQQQXYFGGYPTQWLMCRNFKKFSYYLQBMQAMMMYXCTPSHCPTXXZZSMPHPSHMCLMLDQFYQXSZYYDYJZZHQPDSZGLSTJBCKBXYQZJSGPSXQZQZRQTBDKYXZK"
       "HHGFLBCSMDLDGDZDBLZYYCXNNCSYBZBFGLZZXSWMSCCMQNJQSBDQSJTXXMBLTXZCLZSHZCXRQJGJYLXZFJPHYMZQQYDFQJJLZZNZJCDGZYGCTXMZYSCTLKPHTXHTLBJXJLXSCDQXCBBTJFQZFSLTJBTKQBXXJJLJCHCZDBZJDCZJDCPRNPQCJPFCZLCLZXZDMXMPHJSGZGSZZQLYLWTJPFSYASMCJBTZKYCWMYTCSJJLJCQLWZMALBXYFBPNLSFHTGJWEJJXXGLLJSTGSHJQLZFKCGNNNSZFDEQ"
       "FHBSAQTGYLBXMMYGSZLDYDQMJJRGBJTKGDHGKBLQKBDMBYLXWCXYTTYBKMRTJZXQJBHLMHMJJZMQASLDCYXYQDLQCAFYWYXQHZ";
      std::string result;
      int H = 0;
      int L = 0;
      int W = 0;
      UINT stringlen = strlen(strChs);
      for (UINT i = 0; i < stringlen; i++) {
       H = (UCHAR) (strChs[i + 0]);
       L = (UCHAR) (strChs[i + 1]);
       if (H < 0xA1 || L < 0xA1) {
        result += strChs[i];
        continue;
       } else {
        W = (H - 160) * 100 + L - 160;
       }
       if (W > 1600 && W < 5590) {
        for (int j = 22; j >= 0; j--) {
         if (W >= li_SecPosValue[j]) {
          result += lc_FirstLetter[j];
          i ++;
          break;
         }
        }
        continue;
       } else {
        i++;
        W = (H - 160 - 56) * 94 + L - 161;
        if (W >= 0 && W <= 3007)
         result += ls_SecondSecTable[W];
        else {
         result += (char) H;
         result += (char) L;
        }
       }
      }
      std::string resStr(result);
      return QString::fromStdString(resStr);
}

bool FastBin::searchDir(QString sPath,bool uninstall){
    QDir dir(sPath);
    if (!dir.exists()) return false;
    dir.setFilter(QDir::Dirs|QDir::Files);
    //dir.setSorting(QDir::DirsFirst);
    dir.setSorting(QDir::Time |QDir::Reversed);
    //排序方式 修改时间从小到大
    QFileInfoList list = dir.entryInfoList();
    int i=0,filecont=0;
    do{
        QFileInfo fileInfo = list.at(i);
        if(fileInfo.fileName() == "." || fileInfo.fileName()== "..") {
            i++;
            continue;
        }
        bool bisDir=fileInfo.isDir();
        if(bisDir) {
            qDebug()<<"filedir="<<fileInfo.fileName();
            this->searchDir(sPath + "\\" + fileInfo.fileName(),uninstall);
        }
        else{
            QString baceFileName = fileInfo.baseName();  //不含后缀的文件名
            QString pyFileName(this->topy(baceFileName));
            if(uninstall){
                if(baceFileName.indexOf("卸载",0,Qt::CaseInsensitive)!=-1 || pyFileName.indexOf("uninstall",0,Qt::CaseInsensitive)!=-1){
                    i++;
                    continue;
                }
            }
            QString currentFileName=fileInfo.fileName(); //用于与path结合
            {
                qDebug()<<"filelist sort="<<currentFileName;
                SoftInfo f_si;
                f_si.name = baceFileName;
                f_si.path = sPath + "\\" + currentFileName;
                f_si.pyname = pyFileName;
                QFileInfo file_info(f_si.path);
                QFileIconProvider icon_provider;
                f_si.icon = icon_provider.icon(file_info);
                this->m_SoftInfo.push_back(f_si);
                filecont++;
            }
        }
        i++;
    }while(i<list.size());

    for(int i=0;i<this->m_SoftInfo.size();i++){
        qDebug()<<i<<this->m_SoftInfo[i].name;
        qDebug()<<i<<this->m_SoftInfo[i].path;

    }

    return true;
}

//LoadProgram
bool FastBin::LoadPro(QString Path = "C:\\ProgramData\\Microsoft\\Windows\\Start Menu",bool searchFromLnk = true,bool uninstall=true){
    if(searchFromLnk){
        if(this->searchDir(Path,uninstall)) return true;
        else return false;
    }

}

//FindProgram
std::vector<SoftInfo> FastBin::findPro(QString ProName){
    std::vector<SoftInfo> res;
    for(int i=0;i<this->m_SoftInfo.size();i++){
        if(m_SoftInfo[i].pyname.indexOf(ProName,0,Qt::CaseInsensitive) != -1){
            res.push_back(this->m_SoftInfo[i]);
        }
    }
    return res;
}

bool FastBin::runPro(QString Path){
    Path = QString("file:///") + Path;
    bool is_open = QDesktopServices::openUrl(QUrl(Path, QUrl::TolerantMode));
    return is_open;
}
