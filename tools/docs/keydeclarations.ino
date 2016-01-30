/*
LICENSING INFORMATION

The firmware, known as an "arduino sketch" with the file extension .ino contained within this bundle contains firmware for the UniqueK Diverge Keyboard written by Blahlicus,

this firmware is under a slightly modified version of the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International (CC BY-NC-ND 4.0) license, this means any

individual who downloaded this piece of binary data must give appropriate credit to the original creator of this piece of software, this software is also non-commercial,

anyone except for the original creator may not use this piece of code commercially and this software is also a non-derivatives work, this means, you ARE ALLOWED to remix,

transform, or build upon the material, however, if you remix, transform, or build upon the material, you may not distribute the modified material. for more information about this license, you may visit the following website:

http://creativecommons.org/licenses/by-nc-nd/4.0/

furthermore, this piece of software is provided to you "as is." and the creator of this bundle (Blahlicus) make no express or

implied warrenties whatsoever with respect to its functionality, operability, or use, including, without limitation, any implied warrenties of merchantability, fitness for a

particular purpose, or infringement. the creator (Blahlicus) expressly disclaim any liability whatsoever for any diret, indirect, consequential, incidential and/or special

damages, including, without limitation, lost revenues, lost profits, losses resulting from business interruption or loss of data, lost of functionality of devices including

but not limited to any devices made by the unincorporated company known as "UniqueK" or "Unique Keyboard," regardless of the form of action or legal theory under which the

liability may be asserted, even if advised of the possibility or likelihood of such damages.

INTRODUCTION

hey guys, blahlicus here, this file contains instance names and definitions of key objects, viewing this file is useful for editing the key mapping in the keylayout.ino, but please avoid editing this file unless you know
what you are doing

*/

#include "Arduino.h"
// key definition, alphas and special keys

key ka('a',0);              key kf1(KEY_F1,0);              key klctrl(KEY_LEFT_CTRL,0);
key kb('b',0);              key kf2(KEY_F2,0);              key krctrl(KEY_RIGHT_CTRL,0);
key kc('c',0);              key kf3(KEY_F3,0);              key klshift(KEY_LEFT_SHIFT,0);
key kd('d',0);              key kf4(KEY_F4,0);              key krshift(KEY_RIGHT_SHIFT,0);
key ke('e',0);              key kf5(KEY_F5,0);              key klalt(KEY_LEFT_ALT,0);
key kf('f',0);              key kf6(KEY_F6,0);              key kralt(KEY_RIGHT_ALT,0);
key kg('g',0);              key kf7(KEY_F7,0);              key klwin(KEY_LEFT_GUI,0);
key kh('h',0);              key kf8(KEY_F8,0);              key krwin(KEY_RIGHT_GUI,0);
key ki('i',0);              key kf9(KEY_F9,0);              key kuarrow(KEY_UP_ARROW,0);
key kj('j',0);              key kf10(KEY_F10,0);            key kdarrow(KEY_DOWN_ARROW,0);
key kk('k',0);              key kf11(KEY_F11,0);            key klarrow(KEY_LEFT_ARROW,0);
key kl('l',0);              key kf12(KEY_F12,0);            key krarrow(KEY_RIGHT_ARROW,0);
key km('m',0);              key kbkspace(KEY_BACKSPACE,0);  key kslock(136+71,0);
key kn('n',0);              key ktab(KEY_TAB,0);            key kprtsc(136+70,0);
key ko('o',0);              key kenter(KEY_RETURN,0);       key kpausebrk(136+72,0);
key kp('p',0);              key kesc(KEY_ESC,0);
key kq('q',0);              key kinsert(KEY_INSERT,0);
key kr('r',0);              key kdelete(KEY_DELETE,0);
key ks('s',0);              key kpup(KEY_PAGE_UP,0);
key kt('t',0);              key kpdown(KEY_PAGE_DOWN,0);
key ku('u',0);              key khome(KEY_HOME,0);
key kv('v',0);              key kend(KEY_END,0);
key kw('w',0);              key kcaps(KEY_CAPS_LOCK,0);
key kx('x',0);              key kmenu(136+101,0);
key ky('y',0);              key kspace(32,0);
key kz('z',0);              key knlock(136+83,0);

// symbols
key klbracket(91,0); /* [ { */
key krbracket(93,0); /* ] } */
key kbackslash(92,0); /* \ | */
key ksemicolon(59,0); /* ; : */
key kapostrophe(39,0); /* ' " */
key khyphen(45,0); /* - _ */
key kequals(61,0); /*(+ */
key kslash(47,0); /* / ? */
key kaccent(96,0); /* ` ~ */
key kcomma(44,0); /* , < */
key kperiod(46,0); /* . > */

// numbers
key k0('0',0);
key k1('1',0);
key k2('2',0);
key k3('3',0);
key k4('4',0);
key k5('5',0);
key k6('6',0);
key k7('7',0);
key k8('8',0);
key k9('9',0);

// numpad
key kpslash(220,0); /* numpad / */
key kpasterisk(221,0); /* numpad * */
key kphypen(222,0); /* numpad - */
key kpplus(223,0); /* numpad + */
key kpenter(224,0); /* numpad enter */
key kp1(225,0); /* numpad 1 */
key kp2(226,0); /* numpad 2 */
key kp3(227,0); /* numpad 3 */
key kp4(228,0); /* numpad 4 */
key kp5(229,0); /* numpad 5 */
key kp6(230,0); /* numpad 6 */
key kp7(231,0); /* numpad 7 */
key kp8(232,0); /* numpad 8 */
key kp9(233,0); /* numpad 9 */
key kp0(234,0); /* numpad 0 */
key kpperiod(235,0); /* numpad . */

// special keys
/*   INDEX
1 fn (x) x = layer
2 space fn (x) x = layer
3 layer operation (x) x = up or down
4 media keys (x) x = options
  0 vol up
  1 vol down
  2 vol mute
  3 med play
  4 med stop
  5 med next
  6 med back

255 null
*/
key kfn(1, 1);
key kfn2(2, 1);
key kfn3(3, 1);
key kfn4(4, 1);
key kfn5(5, 1);
key kfn6(6, 1);
key kspacefn(1, 2);
key kspacefn2(2, 2);
key kspacefn3(3, 2);
key kspacefn4(4, 2);
key kspacefn5(5, 2);
key kspacefn6(6, 2);

key klayerdown(0,3);
key klayerup(1,3);

key kvolumeup(0,4);
key kvolumedown(1,4);
key kvolumemute(2,4);
key kmediaplay(3,4);
key kmediapause(4,4);
key kmedianext(5,4);
key kmediaprevious(6,4);

key ktogglefn(1, 5);
key ktogglefn2(2, 5);
key ktogglefn3(3, 5);
key ktogglefn4(4, 5);
key ktogglefn5(5, 5);
key ktogglefn6(6, 5);


key knull(0,255);


void inilayout()
{

    keyLayout[0][3][0] = klctrl;            keyLayout[1][3][0] = klwin;       keyLayout[2][3][0] = kfn;           keyLayout[3][3][0] = klalt;         keyLayout[4][3][0] = kspace;         keyLayout[5][3][0] = knull;
    keyLayout[0][3][1] = klctrl;            keyLayout[1][3][1] = klwin;       keyLayout[2][3][1] = kfn;           keyLayout[3][3][1] = klalt;         keyLayout[4][3][1] = kspace;         keyLayout[5][3][1] = knull;
    keyLayout[0][3][2] = klctrl;            keyLayout[1][3][2] = klwin;       keyLayout[2][3][2] = kfn;           keyLayout[3][3][2] = klalt;         keyLayout[4][3][2] = kspace;         keyLayout[5][3][2] = knull;

    keyLayout[0][2][0] = klshift;           keyLayout[1][2][0] = kz;          keyLayout[2][2][0] = kx;            keyLayout[3][2][0] = kc;            keyLayout[4][2][0] = kv;             keyLayout[5][2][0] = kb;
    keyLayout[0][2][1] = klshift;           keyLayout[1][2][1] = kz;          keyLayout[2][2][1] = kx;            keyLayout[3][2][1] = kc;            keyLayout[4][2][1] = kv;             keyLayout[5][2][1] = kb;
    keyLayout[0][2][2] = klshift;           keyLayout[1][2][2] = kz;          keyLayout[2][2][2] = kx;            keyLayout[3][2][2] = kc;            keyLayout[4][2][2] = kv;             keyLayout[5][2][2] = kb;

    keyLayout[0][1][0] = kcaps;             keyLayout[1][1][0] = ka;          keyLayout[2][1][0] = ks;            keyLayout[3][1][0] = kd;            keyLayout[4][1][0] = kf;             keyLayout[5][1][0] = kg;
    keyLayout[0][1][1] = kcaps;             keyLayout[1][1][1] = klarrow;     keyLayout[2][1][1] = kdarrow;       keyLayout[3][1][1] = krarrow;       keyLayout[4][1][1] = kf;             keyLayout[5][1][1] = kg;
    keyLayout[0][1][2] = kf1;               keyLayout[1][1][2] = kf2;         keyLayout[2][1][2] = kf3;           keyLayout[3][1][2] = kf4;           keyLayout[4][1][2] = kf5;            keyLayout[5][1][2] = kf6;

    keyLayout[0][0][0] = ktab;              keyLayout[1][0][0] = kq;          keyLayout[2][0][0] = kw;            keyLayout[3][0][0] = ke;            keyLayout[4][0][0] = kr;             keyLayout[5][0][0] = kt;
    keyLayout[0][0][1] = kesc;              keyLayout[1][0][1] = kq;          keyLayout[2][0][1] = kuarrow;       keyLayout[3][0][1] = ke;            keyLayout[4][0][1] = kr;             keyLayout[5][0][1] = kt;
    keyLayout[0][0][2] = kaccent;           keyLayout[1][0][2] = k1;          keyLayout[2][0][2] = k2;            keyLayout[3][0][2] = k3;            keyLayout[4][0][2] = k4;             keyLayout[5][0][2] = k5;


}

void inilayout2()
{
  setKeyEEPROM(0, 3, 0, klctrl);            setKeyEEPROM(1, 3, 0, klwin);       setKeyEEPROM(2, 3, 0, kfn);           setKeyEEPROM(3, 3, 0, klalt);         setKeyEEPROM(4, 3, 0, kspacefn);         setKeyEEPROM(5, 3, 0, knull);
  setKeyEEPROM(0, 3, 1, klctrl);            setKeyEEPROM(1, 3, 1, klwin);       setKeyEEPROM(2, 3, 1, kfn);           setKeyEEPROM(3, 3, 1, klalt);         setKeyEEPROM(4, 3, 1, kspacefn);         setKeyEEPROM(5, 3, 1, knull);
  setKeyEEPROM(0, 3, 2, klctrl);            setKeyEEPROM(1, 3, 2, klwin);       setKeyEEPROM(2, 3, 2, kfn);           setKeyEEPROM(3, 3, 2, klalt);         setKeyEEPROM(4, 3, 2, kspacefn);         setKeyEEPROM(5, 3, 2, knull);

  setKeyEEPROM(0, 2, 0, klshift);           setKeyEEPROM(1, 2, 0, kz);          setKeyEEPROM(2, 2, 0, kx);            setKeyEEPROM(3, 2, 0, kc);            setKeyEEPROM(4, 2, 0, kv);             setKeyEEPROM(5, 2, 0, kb);
  setKeyEEPROM(0, 2, 1, klshift);           setKeyEEPROM(1, 2, 1, kz);          setKeyEEPROM(2, 2, 1, kx);            setKeyEEPROM(3, 2, 1, kc);            setKeyEEPROM(4, 2, 1, kv);             setKeyEEPROM(5, 2, 1, kb);
  setKeyEEPROM(0, 2, 2, klshift);           setKeyEEPROM(1, 2, 2, kz);          setKeyEEPROM(2, 2, 2, kx);            setKeyEEPROM(3, 2, 2, kc);            setKeyEEPROM(4, 2, 2, kv);             setKeyEEPROM(5, 2, 2, kb);

  setKeyEEPROM(0, 1, 0, kcaps);             setKeyEEPROM(1, 1, 0, ka);          setKeyEEPROM(2, 1, 0, ks);            setKeyEEPROM(3, 1, 0, kd);            setKeyEEPROM(4, 1, 0, kf);             setKeyEEPROM(5, 1, 0, kg);
  setKeyEEPROM(0, 1, 1, kcaps);             setKeyEEPROM(1, 1, 1, klarrow);     setKeyEEPROM(2, 1, 1, kdarrow);       setKeyEEPROM(3, 1, 1, krarrow);       setKeyEEPROM(4, 1, 1, kf);             setKeyEEPROM(5, 1, 1, kg);
  setKeyEEPROM(0, 1, 2, kf1);               setKeyEEPROM(1, 1, 2, kf2);         setKeyEEPROM(2, 1, 2, kf3);           setKeyEEPROM(3, 1, 2, kf4);           setKeyEEPROM(4, 1, 2, kf5);            setKeyEEPROM(5, 1, 2, kf6);

  setKeyEEPROM(0, 0, 0, ktab);              setKeyEEPROM(1, 0, 0, kq);          setKeyEEPROM(2, 0, 0, kw);            setKeyEEPROM(3, 0, 0, ke);            setKeyEEPROM(4, 0, 0, kr);             setKeyEEPROM(5, 0, 0, kt);
  setKeyEEPROM(0, 0, 1, kesc);              setKeyEEPROM(1, 0, 1, kq);          setKeyEEPROM(2, 0, 1, kuarrow);       setKeyEEPROM(3, 0, 1, ke);            setKeyEEPROM(4, 0, 1, kr);             setKeyEEPROM(5, 0, 1, kt);
  setKeyEEPROM(0, 0, 2, kaccent);           setKeyEEPROM(1, 0, 2, k1);          setKeyEEPROM(2, 0, 2, k2);            setKeyEEPROM(3, 0, 2, k3);            setKeyEEPROM(4, 0, 2, k4);             setKeyEEPROM(5, 0, 2, k5);

}
