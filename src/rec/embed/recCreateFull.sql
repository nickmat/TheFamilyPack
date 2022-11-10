/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/embed/recCreateFull.sql
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     SQL text to create initial database.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     22nd March 2008
 * Copyright:   Copyright (c) 2008..2022, Nick Matthews.
 * Licence:     GNU GPLv3
 *
 *  The Family Pack is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  The Family Pack is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with The Family Pack.  If not, see <http://www.gnu.org/licenses/>.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

    27 Mar 2019  File rename from recCreate.sql to recCreateFull.sql
*/

/* Run recCreateCommon.sql and recCreateMedia.sql script first. */


BEGIN;

CREATE TABLE Associate (
  id INTEGER PRIMARY KEY,
  path TEXT NULL,
  comment TEXT NULL
);

INSERT INTO Associate (id) VALUES(0);

CREATE TABLE Citation (
  id INTEGER PRIMARY KEY,
  higher_id INTEGER NOT NULL,
  ref_id INTEGER NOT NULL REFERENCES Reference(id),
  ref_seq INTEGER NOT NULL,
  rep_id INTEGER NOT NULL REFERENCES Repository(id),
  comment TEXT NULL,
  uid TEXT NOT NULL,
  changed INTEGER NOT NULL
);

INSERT INTO Citation (id, higher_id, ref_id, ref_seq, rep_id, uid, changed)
  VALUES(0,0,0,0,0,'',0);

CREATE TABLE CitationPart (
  id INTEGER PRIMARY KEY,
  cit_id INTEGER NOT NULL REFERENCES Citation(id),
  type_id INTEGER NOT NULL REFERENCES CitationPartType(id),
  val TEXT NOT NULL,
  cit_seq INTEGER NOT NULL,
  comment TEXT NULL
);

INSERT INTO CitationPart (id, cit_id, type_id, val, cit_seq) VALUES(0,0,0,'',0);

CREATE TABLE CitationPartType (
  id INTEGER PRIMARY KEY,
  name TEXT NOT NULL,
  style INTEGER NOT NULL,
  comment TEXT NULL,
  uid TEXT NOT NULL,
  changed INTEGER NOT NULL
);

INSERT INTO CitationPartType (id, name, style, comment, uid, changed)
  VALUES(0, '', 0, '', '', 0);

CREATE TABLE Contact (
  id INTEGER PRIMARY KEY,
  type_id INTEGER NOT NULL REFERENCES ContactType(id),
  list_id INTEGER NOT NULL REFERENCES ContactList(id),
  list_seq INTEGER NOT NULL,
  val TEXT NOT NULL
);

INSERT INTO Contact (id, type_id, list_id, list_seq, val) VALUES(0,0,0,0,'');

CREATE TABLE ContactList (
  id INTEGER PRIMARY KEY,
  ind_id INTEGER REFERENCES Individual(id)
);

CREATE TABLE ContactType (
  id INTEGER PRIMARY KEY,
  name TEXT NOT NULL,
  uid TEXT NOT NULL,
  changed INTEGER NOT NULL
);
/* See below for id=0 */

CREATE TABLE Date (
  id INTEGER PRIMARY KEY,
  jdn INTEGER NOT NULL,
  range INTEGER NOT NULL,
  rel_id INTEGER NOT NULL REFERENCES RelativeDate(id),
  type INTEGER NOT NULL,
  descrip TEXT NOT NULL,
  record_sch INTEGER NOT NULL,
  display_sch INTEGER NOT NULL,
  uid TEXT NOT NULL,
  changed INTEGER NOT NULL
);

INSERT INTO Date (
  id, jdn, range, rel_id, type, descrip, record_sch, display_sch, uid, changed)
  VALUES(0,0,0,0,0,'',0,0,'',0);

CREATE TABLE Event (
  id INTEGER PRIMARY KEY,
  title TEXT NOT NULL,
  higher_id INTEGER NOT NULL,
  type_id INTEGER NOT NULL REFERENCES EventType(id),
  date1_id INTEGER NOT NULL,
  date2_id INTEGER NOT NULL,
  place_id INTEGER NOT NULL,
  note TEXT NOT NULL,
  date_pt INTEGER NOT NULL,
  user_ref TEXT
);

INSERT INTO Event (
  id, title, higher_id, type_id, date1_id, date2_id, place_id, note, date_pt)
  VALUES(0,'',0,0,0,0,0,'',0);

CREATE TABLE Eventa (
  id INTEGER PRIMARY KEY,
  title TEXT NOT NULL,
  ref_id INTEGER NOT NULL REFERENCES Reference(id),
  type_id INTEGER NOT NULL REFERENCES EventType(id),
  date1_id INTEGER NOT NULL REFERENCES Date(id),
  date2_id INTEGER NOT NULL REFERENCES Date(id),
  place_id INTEGER NOT NULL REFERENCES Place(id),
  note TEXT NOT NULL,
  date_pt INTEGER NOT NULL,
  uid TEXT NOT NULL,
  changed INTEGER NOT NULL
);

INSERT INTO Eventa (
  id, title, ref_id, type_id, date1_id, date2_id, place_id, note, date_pt, uid, changed)
  VALUES(0,'',0,0,0,0,0,'',0,'',0);

CREATE TABLE EventaPersona (
  id INTEGER PRIMARY KEY,
  eventa_id INTEGER NOT NULL REFERENCES Eventa(id),
  per_id INTEGER NOT NULL REFERENCES Persona(id),
  role_id INTEGER NOT NULL REFERENCES EventTypeRole(id),
  note TEXT NOT NULL,
  per_seq INTEGER NOT NULL
);

INSERT INTO EventaPersona (
  id, eventa_id, per_id, role_id, note, per_seq)
  VALUES(0,0,0,0,'',0);

CREATE TABLE EventEventa (
  id INTEGER PRIMARY KEY,
  event_id INTEGER NOT NULL REFERENCES Event(id),
  eventa_id INTEGER NOT NULL REFERENCES Eventa(id),
  conf FLOAT NOT NULL,
  note TEXT
);

INSERT INTO EventEventa (id, event_id, eventa_id, conf) VALUES(0,0,0,'');

CREATE TABLE EventType (
  id INTEGER PRIMARY KEY,
  grp INTEGER NOT NULL,
  name TEXT NOT NULL,
  uid TEXT NOT NULL,
  changed INTEGER NOT NULL
);

CREATE TABLE EventTypeRole (
  id INTEGER PRIMARY KEY,
  type_id INTEGER NOT NULL REFERENCES EventType(id),
  prime INTEGER NOT NULL,
  official INTEGER NOT NULL,
  name TEXT NOT NULL,
  uid TEXT NOT NULL,
  changed INTEGER NOT NULL
);

INSERT INTO EventType (id, grp, name, uid, changed) VALUES(0,0,'','',0);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(0,0,0,0,'','',0);

INSERT INTO EventType (id, grp, name, uid, changed) VALUES(-1, 1, 'Birth', '30AB007B03C8BF584A53124EB8D652697E84', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-1, -1, 1, 0, 'Born', '6294C833BCF9D2E0F8DDDEC4946441F901B4', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-2, -1, 0, 0, 'Mother', '59D8C78FC6E8102B214147C6A0A25012832F', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-3, -1, 0, 1, 'Midwife', '527A6A76412AFF9C8DE1ABA399D8304655AE', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-4, -1, 0, 0, 'Present', '3C0E358DFDDFF7989230FE002F9FC61AE523', 2459752);

INSERT INTO EventType (id, grp, name, uid, changed) VALUES(-2, 5, 'Death', '9D456F509BCB5CBEFB891695B48FAB5E9C75', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-5, -2, 1, 0, 'Died', '2753766036C229794AEE257200EA8DAEDECA', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-6, -2, 0, 0, 'Present', '3721F9AED08D02AB242268E6517D2EDB74A7', 2459752);

INSERT INTO EventType (id, grp, name, uid, changed) VALUES(-3, 3, 'Marriage', '4C763908AD6A87F5453ADE212EAF8472E793', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-7, -3, 1, 0, 'Groom', 'EBBCF29CE75DEB1B57A2C0196245C14C0518', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-8, -3, 2, 0, 'Bride', '370B504243943119A9A74C8B481A9CD2ECEA', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-9, -3, 0, 1, 'Officiator', '74B2CDEFCED43777C94C3DD493B37D0F2A7C', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-10, -3, 0, 0, 'Witness', 'BE6933D1F76F2CD6B62F4F0275A505B59D64', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-11, -3, 0, 0, 'Father of Groom', '047FB29EE359BE626B2F8ED84BDC3BC455EF', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-12, -3, 0, 0, 'Mother of Groom', '1358514D43426F30E12BE41CF39C9FAD1453', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-13, -3, 0, 0, 'Father of Bride', '9C3E06785825611CD76CED8C310016348965', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-14, -3, 0, 0, 'Mother of Bride', 'D13491A16857D377E16AD3E3187D2063590A', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-15, -3, 0, 0, 'Give away Bride', '66C12CF765541AAA50FB4CED3C9BBE866681', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-16, -3, 0, 0, 'Maid of Honour', 'ADDBF1757B7C467F7C1B9305317B29B26070', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-17, -3, 0, 0, 'Bridesmaid', '9D964DB5D4BB2BA65C4D23D8809EEE4F9488', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-18, -3, 0, 0, 'Best Man', '1E4068FB67D4DE9AB3171DC7CC0E14162677', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-19, -3, 0, 0, 'Pageboy', 'C56BCF2BBBBC3A8F1D10CAB43A33E746AF66', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-20, -3, 0, 0, 'Present', '5B1E1118786681C12A4C06EDF10AD1251C3F', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-59, -3, 3, 0, 'Spouse', 'ACFCFE744A4FC5CCEFDFD0B68B922513ED45', 2459752);

INSERT INTO EventType (id, grp, name, uid, changed) VALUES(-4, 2, 'Baptism', '70933A4FE1C53D2726E2DDBE540D2C0BD1AC', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-21, -4, 1, 0, 'Baptised', '6B6CB578797164D8C2EA6809B94E261E9254', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-22, -4, 0, 0, 'Parent', 'D46C5E4B8857CEE439D11F1C69394B7F2BDD', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-23, -4, 0, 0, 'God Parent', '25E14F730376D3D6E86BAA72B1192AADFA15', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-24, -4, 0, 1, 'Officiator', '603C86B8542C0EA4C6E64D3EAD9663BAA3C8', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-25, -4, 0, 0, 'Present', 'B7DDBF0EE6D66C6CA696FE1A2D68B9EB8292', 2459752);

INSERT INTO EventType (id, grp, name, uid, changed) VALUES(-5, 6, 'Burial', 'B280BF2B8CE00795F1DF2572BB7BAB026E62', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-26, -5, 1, 0, 'Deceased', '980587CF544175E55A02BA7C343E629CE49A', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-27, -5, 0, 1, 'Officiator', '86D47917CAB0A4836583EBC67ADD38B76A63', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-28, -5, 0, 0, 'Present', '3D79C782650F98F9C103D4D03289520A83AB', 2459752);

INSERT INTO EventType (id, grp, name, uid, changed) VALUES(-6, 7, 'Adult Baptism', 'A2938143B96EDAE92E402CAECDE1FDCCA288', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-29, -6, 1, 0, 'Baptised', '2F802E3F827490E491ED7F022CD5F80D8B12', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-30, -6, 0, 1, 'Officiator', '8A152316FCA79A363BCC83E9F9682B6CB6B3', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-31, -6, 0, 0, 'Present', '53534D02E6C94872325323C5B09F6DFB828C', 2459752);

INSERT INTO EventType (id, grp, name, uid, changed) VALUES(-7, 7, 'Census', '8B2158196ACCDF1AB4A438F6B97922193FF6', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-32, -7, 1, 0, 'Listed', '45D36CC7EC0B39D46B9205885571883960F3', 2459752);

INSERT INTO EventType (id, grp, name, uid, changed) VALUES(-8, 7, 'Confirmation', 'D749C38DB0A5B8862A7F67C71348A3825AC9', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-33, -8, 1, 0, 'Confirmed', 'AFFB9AFE5A2A54653A0752B2812A3FF19F2A', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-34, -8, 0, 1, 'Officiator', '30A9EDE2C9D197F2FA47498E6CCB3A217509', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-35, -8, 0, 0, 'Present', '06A3B3281C6E916F44A056F4D5E924F816F1', 2459752);

INSERT INTO EventType (id, grp, name, uid, changed) VALUES(-9, 4, 'Divorce', '5F22AAF1C26A49037BC21DB918000317D900', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-36, -9, 1, 0, 'Husband', '722D3DC4759ECC67704C1F5305433BB249DC', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-37, -9, 2, 0, 'Wife', 'F50834023F0CBF1600EFFFD37C43A5FE7611', 2459752);

INSERT INTO EventType (id, grp, name, uid, changed) VALUES(-10, 7, 'Emigration', '188C09CBB315B850871C14E6E3167B91EA13', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-38, -10, 1, 0, 'Emigrant', 'F6CE7D384D38B6006131E3CF05029B1AB466', 2459752);

INSERT INTO EventType (id, grp, name, uid, changed) VALUES(-11, 7, 'Immigration', '601CCC7985405F97C9405751B33F44DE4188', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-39, -11, 1, 0, 'Immigrant', '38B130B59F7FC9F78E52235B2CC1F447328B', 2459752);

INSERT INTO EventType (id, grp, name, uid, changed) VALUES(-12, 7, 'Graduation', 'C9325D190689AB25609F681A3AFC3CD59873', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-40, -12, 1, 0, 'Graduate', 'D7F462E3E16E2FDCF54E7BB64D10AED8C149', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-41, -12, 0, 0, 'Present', '84100E33B6EBA4030BF2859F30569C2484FC', 2459752);

INSERT INTO EventType (id, grp, name, uid, changed) VALUES(-13, 7, 'Probate', 'A958ED4A33C1A8068631D92812401B2E2DB6', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-42, -13, 1, 0, 'Deceased', '1D27D815BDBE87F4DEE93921CC0A489C029E', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-43, -13, 0, 0, 'Executor', '85A72F1867C30005C3E3C8AFC0CAF5BFFDB4', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-44, -13, 0, 1, 'Adjudicator', '23F148EE526D13BFFF0AA38DF2B066C6E28C', 2459752);

INSERT INTO EventType (id, grp, name, uid, changed) VALUES(-14, 7, 'Will', 'A43B77FAA6606717D17B864945ADB042D3D9', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-45, -14, 1, 0, 'Subject', '3E937C13782A350FB56C12FCBF425DB18464', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-46, -14, 0, 0, 'Executor', '6778DE2C39CA3D81399AD3861ED4C6B03EDB', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-47, -14, 0, 0, 'Beneficiary', 'F2A598516179B89FBA44F72AD8D15BC59954', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-48, -14, 0, 1, 'Solicitor', '0E0546B7FE61E3437C721612E1655E29780A', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-49, -14, 0, 0, 'Witness', '1B7C454890F1695FF87CC63D098178B0962E', 2459752);

INSERT INTO EventType (id, grp, name, uid, changed) VALUES(-15, 2, 'Register Birth', '8C347D7CE909C4E123C578F3C1F934CA5BF9', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-50, -15, 1, 0, 'Born', '81451C911D32C7F7AE4125C8F88565559382', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-51, -15, 0, 0, 'Parent', '194C35B62D872374E52277B84817980ED69E', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-52, -15, 0, 0, 'Registrant', '5C7BA6874EF0DADD5600A8C1ACD90A6BB244', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-53, -15, 0, 1, 'Registrar', '1B380CD1A593F789B787103EB4619B1539FE', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-54, -15, 0, 0, 'Mentioned', '7CEC5F925775C9847E3FE2E3A126565B6C2A', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-60, -15, 0, 0, 'Mother', '1A7EFE1584ED9579D7A90B11AF44C8F67765', 2459752);

INSERT INTO EventType (id, grp, name, uid, changed) VALUES(-16, 6, 'Register Death', '45131053450AAFF043D1FFA2B57573DCD75C', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-55, -16, 1, 0, 'Died', '0683188FDAB4D0DFC94FE19146ED05E514E5', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-56, -16, 0, 0, 'Registrant', '2E01C860F7DB33A2F192F3C6306F9F5CD429', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-57, -16, 0, 1, 'Registrar', '2C0354516E3368917EE7470E470CD49BEAD8', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-58, -16, 0, 0, 'Mentioned', 'E4EB7D2283DE5E6E569DB2BCA6FE2DFAC786', 2459752);

INSERT INTO EventType (id, grp, name, uid, changed) VALUES(-17, 8, 'Residence', '904EB30BB56D46F20BF15D3BD1EC60D27932', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-61, -17, 1, 0, 'Family', '40D36C4B1F763EAA61A334B78A4410374B93', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-62, -17, 1, 0, 'Visitor', '4658360D56D2A8225A4FFE76A69F63E47C4F', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-63, -17, 1, 0, 'Lodger', '071F0D3B669300A890AD29F5C19834C1B8E6', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-64, -17, 1, 0, 'Boarder', 'E427AC312363F7B9CE2FC710764EE9711032', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-77, -17, 1, 0, 'Summary', 'FA93BB7BC8AF566CE5CA22698208154D22E1', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-85, -17, 1, 0, 'Staff', '47C012FC3246F3ED916EBDDE8ECFC7ED1813', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-86, -17, 1, 0, 'Inmate', '2A91334CAF9E75291AEB13CDE2C7EC64038F', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-87, -17, 1, 0, 'Resident', '44821AA9C75ED4ECC7F5DDDDDA615CE35E61', 2459752);

INSERT INTO EventType (id, grp, name, uid, changed) VALUES(-18, 8, 'Occupation', '7ACC2C0D44AB258632F2F7200B1ABEDD14C1', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-65, -18, 1, 0, 'Summary', '26DD261E46203A04BAFC9DB4719C91AC3C49', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-66, -18, 0, 0, 'Employer', '701D3345C19A06D5335E80EB9165D7AAAEED', 2459752);

INSERT INTO EventType (id, grp, name, uid, changed) VALUES(-19, 8, 'Condition', '2B9BFD3E4222364938364518EACEF34BA58F', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-67, -19, 1, 0, 'Summary', '43EE52E796C6CD2A07D2F971BFDE0049E63F', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-78, -19, 1, 0, 'Single', '09231B6FAA16992813B9436123347E69E5B1', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-79, -19, 1, 0, 'Married', '74D4E342FA0DBFADBD9E8953F8574F2BE0FF', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-80, -19, 1, 0, 'Partner', '2E6CF9CC1BEC5B1FE187F5F510336FE4C816', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-81, -19, 1, 0, 'Civil Partner', '07E388D822E3C225FF5E7608750D8A345118', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-82, -19, 1, 0, 'Widowed', 'E07B5A82032DCC4B117EEA9807C76CF4BD14', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-83, -19, 1, 0, 'Divorced', '4288622410FBDDD10352C29510EC3B89759A', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-84, -19, 1, 0, 'Separated', '08EDD626A4C65860FDC1D57897E4D3168250', 2459752);

INSERT INTO EventType (id, grp, name, uid, changed) VALUES(-20, 3, 'Civl Partnership', 'DEA4143114BEEC17045BBA744FBD1CBD0ED7', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-68, -20, 3, 0, 'Partner', 'B3B8F286F54F9EF2609FFD1477A7391A3899', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-69, -20, 0, 1, 'Officiator', 'DF91CF34FA1D3B04B1DA951605E1AE2EC179', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-70, -20, 0, 0, 'Witness', '99555FED0E1A2E0F265AE943DF4CDA2A7A88', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-71, -20, 0, 0, 'Present', '36827CA6269ADED1C61EB60E58C2AE05BE32', 2459752);

INSERT INTO EventType (id, grp, name, uid, changed) VALUES(-21, 9, 'Relation', '789B829792C6BF41E9E2DA2DADD73119249C', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-72, -21, 1, 0, 'Subject', 'EACEDD6D072E2075FBE3797E2BB99AD9F839', 2459752);

INSERT INTO EventType (id, grp, name, uid, changed) VALUES(-22, 10, 'Family', '52EEDA65F1A6102CC9599D265B3C181A0046', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-73, -22, 1, 0, 'Husband', '62ED6136546784602D2DD587186137C0ABE9', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-74, -22, 2, 0, 'Wife', 'AD2AC696CE92F21DE36A9D5527018955E77A', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-75, -22, 3, 0, 'Partner', '7D21EC88162CAB80E13C536AC415E7F9126F', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-76, -22, 0, 0, 'Child', '0E4989ADFD94E53CED9BEED67C3D01BD0281', 2459752);

INSERT INTO EventType (id, grp, name, uid, changed) VALUES(-23, 7, 'Media', 'C86CC13C6CCFDB2DB805A8AB0B3FC11FAE3A', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-88, -23, 1, 0, 'Subject', 'A9C3A735798018D815129BFE7617F01F8D5E', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-89, -23, 0, 0, 'Producer', '8D27BA1F504D7471241D7BD9DB27D3BE37B7', 2459752);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(-90, -23, 0, 0, 'Commentator', '25A5B0991319C04ADE60A87908D1BF8BCBEA', 2459752);

/* Next EventTypeRole id = -91 */

CREATE TABLE Family (
  id INTEGER PRIMARY KEY,
  husb_id INTEGER,
  wife_id INTEGER
);

INSERT INTO Family (id) VALUES(0);

CREATE TABLE FamilyEvent (
  id INTEGER PRIMARY KEY,
  fam_id INTEGER NOT NULL REFERENCES Family(id),
  event_id INTEGER NOT NULL REFERENCES Event(id),
  note TEXT,
  fam_seq INTEGER NOT NULL
);

INSERT INTO FamilyEvent (id, fam_id, event_id, fam_seq) VALUES(0,0,0,0);

CREATE TABLE FamilyEventa (
  id INTEGER PRIMARY KEY,
  fam_id INTEGER NOT NULL REFERENCES Family(id),
  eventa_id INTEGER NOT NULL REFERENCES Eventa(id),
  conf FLOAT NOT NULL,
  note TEXT
);

INSERT INTO FamilyEventa (id, fam_id, eventa_id, conf) VALUES(0,0,0,0);

CREATE TABLE FamilyIndEventa (
  id INTEGER PRIMARY KEY,
  fam_ind_id INTEGER NOT NULL REFERENCES FamilyIndividual(id),
  eventa_id INTEGER NOT NULL REFERENCES Eventa(id),
  conf FLOAT NOT NULL,
  note TEXT
);

INSERT INTO FamilyIndEventa (id, fam_ind_id, eventa_id, conf) VALUES(0,0,0,0);

CREATE TABLE FamilyIndividual (
  id INTEGER PRIMARY KEY,
  fam_id INTEGER NOT NULL,
  ind_id INTEGER NOT NULL,
  seq_child INTEGER NOT NULL,
  seq_parent INTEGER NOT NULL
);

INSERT INTO FamilyIndividual (
  id, fam_id, ind_id, seq_child,seq_parent) VALUES(0,0,0,0,0);

CREATE TABLE Gallery (
  id INTEGER PRIMARY KEY,
  title TEXT NOT NULL,
  note TEXT NULL,
  uid TEXT NOT NULL,
  changed INTEGER NOT NULL
);

INSERT INTO Gallery (id, title, note, uid, changed) VALUES(0,'','','',0);

CREATE TABLE GalleryMedia (
  id INTEGER PRIMARY KEY,
  title TEXT NULL,
  gal_id INT NOT NULL REFERENCES Gallery(id),
  med_id INT NOT NULL REFERENCES Media(id),
  med_seq INT NOT NULL
);

INSERT INTO GalleryMedia (id, gal_id, med_id, med_seq) VALUES(0,0,0,0);

CREATE TABLE Individual (
  id INTEGER PRIMARY KEY,
  sex INTEGER NOT NULL,
  fam_id INTEGER NOT NULL,
  note TEXT NOT NULL,
  privacy INTEGER NOT NULL,
  name TEXT,
  surname TEXT,
  epitaph TEXT
);

INSERT INTO Individual (id, sex, fam_id, note, privacy) VALUES(0,0,0,'',0);

CREATE TABLE IndividualEvent (
  id INTEGER PRIMARY KEY,
  higher_id INTEGER NOT NULL,
  ind_id INTEGER NOT NULL REFERENCES Individual(id),
  event_id INTEGER NOT NULL REFERENCES Event(id),
  role_id INTEGER NOT NULL REFERENCES EventTypeRole(id),
  note TEXT NOT NULL,
  ind_seq INTEGER NOT NULL
);

INSERT INTO IndividualEvent (
  id, higher_id, ind_id, event_id, role_id, note, ind_seq)
  VALUES(0,0,0,0,0,'',0);

CREATE TABLE IndividualPersona (
  id INTEGER PRIMARY KEY,
  ind_id INTEGER NOT NULL REFERENCES Individual(id),
  per_id INTEGER NOT NULL REFERENCES Persona(id),
  conf FLOAT NOT NULL,
  note TEXT
);

INSERT INTO IndividualPersona (id, ind_id, per_id, conf) VALUES(0,0,0,0);

CREATE TABLE Media (
  id INTEGER PRIMARY KEY,
  data_id INT NOT NULL REFERENCES MediaData(id),
  ass_id INT NOT NULL REFERENCES Associate(id),
  ref_id INT NOT NULL REFERENCES Reference(id),
  ref_seq INT NOT NULL,
  privacy INT NOT NULL,
  title TEXT NULL,
  note TEXT NULL,
  uid TEXT NOT NULL,
  changed INTEGER NOT NULL
);

INSERT INTO Media (
  id, data_id, ass_id, ref_id, ref_seq, privacy, title, note, uid, changed)
  VALUES(0,0,0,0,0,0,'','','',0);

/* Table MediaData created in recCreateMedia.sql */

CREATE TABLE Name (
  id INTEGER PRIMARY KEY,
  ind_id INTEGER NOT NULL,
  per_id INTEGER NOT NULL,
  style_id INTEGER NOT NULL REFERENCES NameStyle(id),
  sequence INTEGER
);

INSERT INTO Name (id, ind_id, per_id, style_id) VALUES(0,0,0,0);

CREATE TABLE NamePart (
  id INTEGER PRIMARY KEY,
  name_id INTEGER NOT NULL REFERENCES Name(id),
  type_id INTEGER NOT NULL REFERENCES NamePartType(id),
  val TEXT,
  sequence INTEGER NOT NULL
);

INSERT INTO NamePart (id, name_id, type_id, sequence) VALUES(0,0,0,0);

CREATE TABLE NamePartType (
  id INTEGER PRIMARY KEY,
  grp INTEGER NOT NULL,
  name TEXT NOT NULL,
  uid TEXT NOT NULL,
  changed INTEGER NOT NULL
);

/* matches enum StdNameType */
INSERT INTO NamePartType (id, grp, name, uid, changed) VALUES( 0, 0, '', '', 0);
INSERT INTO NamePartType (id, grp, name, uid, changed) VALUES(-1, 1, 'Given name', 'D078B79DEA7D7C5E6954D9BD9A3F77951583', 2459715);
INSERT INTO NamePartType (id, grp, name, uid, changed) VALUES(-2, 1, 'Surname', 'C8FA1239479F03CE5A4A9D9462DA1074599E', 2459715 );
INSERT INTO NamePartType (id, grp, name, uid, changed) VALUES(-3, 1, 'Post name', 'B4FC970919A55CBD630EC6A9109F692342B8', 2459715);

CREATE TABLE NameStyle (
  id INTEGER PRIMARY KEY,
  name TEXT NOT NULL,
  uid TEXT NOT NULL,
  changed INTEGER NOT NULL
);

/* matches enum recNameStyle::Style */
INSERT INTO NameStyle (id, name, uid, changed) VALUES(0, 'Default', '', 0);
INSERT INTO NameStyle (id, name, uid, changed) VALUES(-1, 'Birth name', '9E8D131956EFBA85EE89134A9EBD43004DF8', 2459715);
INSERT INTO NameStyle (id, name, uid, changed) VALUES(-2, 'Married name', 'CCEF089DAD05903B8825EF5FC8F5A5DA140B', 2459715);
INSERT INTO NameStyle (id, name, uid, changed) VALUES(-3, 'Alias', '67F2C0CDB179EE99E6D3C4B82C9BAAAEEB5B', 2459715);

CREATE TABLE Persona (
  id INTEGER PRIMARY KEY,
  sex INTEGER NOT NULL,
  ref_id INTEGER NOT NULL REFERENCES Reference(id),
  note TEXT,
  uid TEXT NOT NULL,
  changed INTEGER NOT NULL
);

INSERT INTO Persona (id, sex, ref_id, note, uid, changed) VALUES(0,0,0,'','',0);

CREATE TABLE Place (
  id INTEGER PRIMARY KEY,
  date1_id INTEGER NOT NULL REFERENCES Date(id),
  date2_id INTEGER NOT NULL REFERENCES Date(id),
  uid TEXT NOT NULL,
  changed INT NOT NULL
);

INSERT INTO Place (id, date1_id, date2_id, uid, changed)
  VALUES(0,0,0,'',0);

CREATE TABLE PlacePart (
  id INTEGER PRIMARY KEY,
  type_id INTEGER,
  place_id INTEGER,
  val TEXT,
  sequence INTEGER
);

INSERT INTO PlacePart (id) VALUES(0);

CREATE TABLE PlacePartType (
  id INTEGER PRIMARY KEY,
  name TEXT NOT NULL,
  uid TEXT NOT NULL,
  changed INT NOT NULL
);

INSERT INTO PlacePartType (id, name, uid, changed) VALUES(0, '', '', 0);
INSERT INTO PlacePartType (id, name, uid, changed) VALUES(-1, 'Address', '73D067F49E86C542C3E237AFC50BE77F8A11', 0);

CREATE TABLE Reference (
  id INTEGER PRIMARY KEY,
  higher_id INTEGER,
  title TEXT NOT NULL,
  statement TEXT NOT NULL,
  res_id INTEGER NULL REFERENCES Researcher(id),
  user_ref TEXT NULL,
  uid TEXT NOT NULL,
  changed INT NOT NULL
);

INSERT INTO Reference (id, title, statement, uid, changed)
  VALUES(0,'','','',0);

CREATE TABLE ReferenceEntity (
  id INTEGER PRIMARY KEY,
  ref_id INTEGER,
  entity_type INTEGER,
  entity_id INTEGER,
  sequence INTEGER
);

INSERT INTO ReferenceEntity (id) VALUES(0);

CREATE TABLE RelativeDate (
  id INTEGER PRIMARY KEY,
  val INTEGER,
  range INTEGER,
  unit INTEGER,
  base_id INTEGER NOT NULL REFERENCES Date(id),
  type INTEGER,
  scheme INTEGER
);

INSERT INTO RelativeDate (id, base_id) VALUES(0,0);

CREATE TABLE Repository (
  id INTEGER PRIMARY KEY,
  name TEXT NOT NULL,
  note TEXT NULL,
  con_list_id INTEGER NULL REFERENCES ContactList(id),
  uid TEXT NOT NULL,
  changed INTEGER NOT NULL
);

INSERT INTO Repository (id, name, uid, changed) VALUES(0,'','',0);

CREATE TABLE Researcher (  /* See System Settings below for initial entries */
  id INTEGER PRIMARY KEY,
  name TEXT NOT NULL,
  comment TEXT,
  con_list_id INTEGER REFERENCES ContactList(id),
  uid TEXT NOT NULL,
  changed INTEGER NOT NULL
);

CREATE TABLE System (  /* See System Settings below for initial entries */
  id INTEGER PRIMARY KEY,
  val TEXT NOT NULL
);

CREATE TABLE User (  /* See System Settings below for initial entries */
  id INTEGER PRIMARY KEY,
  res_id INTEGER NOT NULL REFERENCES Researcher(id)
);

CREATE TABLE UserSetting (  /* See System Settings below for initial entries */
  id INTEGER PRIMARY KEY,
  user_id INTEGER NOT NULL REFERENCES User(id),
  property INTEGER NOT NULL,
  val TEXT NOT NULL
);

/* Create default settings */
INSERT INTO ContactType (id, name, uid, changed)
  VALUES(0, '', '', 0);
INSERT INTO ContactType (id, name, uid, changed)
  VALUES(-1, 'Address', '88815CB7641A5C15A6B47B40E69DE654DD52', 2459664);
INSERT INTO ContactType (id, name, uid, changed)
  VALUES(-2, 'Telephone', '7143E6D4D916C849F2B4FC6554AE5B421483', 2459664);
INSERT INTO ContactType (id, name, uid, changed)
  VALUES(-3, 'Mobile', 'D5914CBACD1E86412EB4771C1E015BCBD882', 2459664);
INSERT INTO ContactType (id, name, uid, changed)
  VALUES(-4, 'Email', '2A56952B37D688AD0F795B059A82619E857A', 2459664);
INSERT INTO ContactType (id, name, uid, changed)
  VALUES(-5, 'Website', '0913E9393D6F676F74252E9F18516D201CFD', 2459664);
INSERT INTO ContactType (id, name, uid, changed)
  VALUES(-6, 'Fax', 'D717ACECD3D1DF6E663C9788BFB330350F50', 2459664);

INSERT INTO Researcher (id, name, comment, con_list_id, uid, changed) VALUES
  (0, '', NULL, NULL, '', 0);
INSERT INTO Researcher (id, name, comment, con_list_id, uid, changed) VALUES
  (-1, 'Anonymous', NULL, NULL, 'E16C3575699D77C1BABD0C582A44C6FA3E4A', 2459675);

INSERT INTO User (id, res_id) VALUES(1, 0); /* Set User U1 to unknown */

INSERT INTO System (id, val) VALUES(1, '1'); /* User U1 */

INSERT INTO UserSetting (id, user_id, property, val) VALUES(1, 1, 1, 'NI');

/* Table Version created in recCreateCommon.sql */

/* The Version table row 1 is the full TFPD database */
INSERT INTO Version (id, major, minor, revision, test) VALUES(1, 0, 0, 10, 44);

COMMIT;

/* End of src/rec/embed/recCreateFull.sql */
