/* ../tfpText.h - File created by file2cpp 1.0.0 */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/tfp/embed/tfpText.f2c
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Screen texts collected from files. Format file for file2cpp.
 * Author:      Nick Matthews
 * Created:     26 September 2010
 * Copyright:   Copyright (c) 2010 ~ 2017, Nick Matthews.
 * Website:     http://thefamilypack.org
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

*/

static const char s_startup_htm[] =  /* startup.htm */
 "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n"
 "<html>\n"
 "<head>\n"
 "<title>The Family Pack StartUp</title>\n"
 "<meta http-equiv='Content-Type' content='text/html;charset=utf-8'>\n"
 "<link rel='stylesheet' type='text/css' href='memory:tfp.css'>\n"
 "</head>\n"
 "<body>\n"
 "<table class='logo'>\n"
 "<tr>\n"
 "<td>\n"
 "<img src='memory:logo6.png'>\n"
 "</td>\n"
 "<td class='title'>\n"
 "<font size='+4'><b>The Family Pack</b></font>\n"
 "</td>\n"
 "</tr>\n"
 "</table>\n"
 "<div class='pagesel control'>\n"
 "<p>\n"
 "<br><br><b>Actions:-</b><br>\n"
 "<a href='tfpc:Open'>Open an existing Database</a>\n"
 "<br>\n"
 "<a href='tfpc:New'>Create a new Database</a>\n"
 "<br>\n"
 "<a href='tfpc:Import'>Import a GEDCOM file</a>\n"
 "</p>\n"
 "</div>\n"
 "<p>\n"
 "<a class='web' href='http://thefamilypack.org'>http://thefamilypack.org</a><br>\n"
 "<br>\n"
 "<b>TFP</b> %s\n"
 "</p>\n"
 "</body>\n"
 "</html>\n";

static const char s_tfp_css[] =  /* tfp.css */
 "body {\n"
 "color: #444;\n"
 "background-color: Ivory;\n"
 "}\n"
 "table.logo {\n"
 "border-collapse: collapse;\n"
 "width: 100%;\n"
 "}\n"
 "table.logo td {\n"
 "background-color: #e0e0f0;\n"
 "margin: 0;\n"
 "padding: 0.5em;\n"
 "border: 0 none black;\n"
 "}\n"
 "table.logo td.title {\n"
 "text-align: center;\n"
 "}\n"
 "h1 {\n"
 "text-align: center;\n"
 "}\n"
 "img {\n"
 "margin: 0;\n"
 "padding: 0;\n"
 "border: 0 none black;\n"
 "}\n"
 "a {\n"
 "color: #444;\n"
 "text-decoration: none;\n"
 "}\n"
 "a:hover {\n"
 "color: #000;\n"
 "text-decoration: underline;\n"
 "}\n"
 "a.web:hover {\n"
 "color: #000;\n"
 "text-decoration: underline;\n"
 "}\n"
 "div.tfp p.indent {\n"
 "text-indent: -1em;\n"
 "padding-left: 1em;\n"
 "}\n"
 "div.tfp table.core {\n"
 "border-collapse: collapse;\n"
 "margin: 0 auto;\n"
 "}\n"
 "div.tfp td {\n"
 "background-color: #f4ebed;\n"
 "border: 1px solid #777;\n"
 "border-width: 1px 2px;\n"
 "padding: 0.2em 1em 0.2em 1em;\n"
 "text-align: left;\n"
 "}\n"
 "div.tfp td.male {\n"
 "background-color: #d0fdff;\n"
 "text-align: center;\n"
 "font: bold 1.2em \"Times New Roman\", serif;\n"
 "}\n"
 "div.tfp td.fem {\n"
 "background-color: #ffcccc;\n"
 "text-align: center;\n"
 "font: bold 1.2em \"Times New Roman\", serif;\n"
 "}\n"
 "div.tfp td.neut {\n"
 "background-color: #eeeeee;\n"
 "text-align: center;\n"
 "font: bold 1.2em \"Times New Roman\", serif;\n"
 "}\n"
 "div.tfp td.both {\n"
 "text-align: center;\n"
 "}\n"
 "div.tfp td.couple {\n"
 "width: 50%;\n"
 "padding: 0.3em 1em 0.3em 1em;\n"
 "border: 4px solid #777;\n"
 "}\n"
 "div.tfp td.couple a {\n"
 "font-size: 1.5em;\n"
 "}\n"
 "div.tfp td.subject a {\n"
 "font-size: 1.5em;\n"
 "}\n"
 "div.tfp td.odd {\n"
 "background-color: #f4ebed;\n"
 "}\n"
 "div.tfp td.even {\n"
 "background-color: #faf0f0;\n"
 "}\n"
 "div.tfp table.parent {\n"
 "border-collapse: collapse;\n"
 "width: 90%;\n"
 "padding: 0;\n"
 "margin: 0.2em auto;\n"
 "border: 2px solid #777;\n"
 "}\n"
 "div.tfp table.frame {\n"
 "margin: 1em auto;\n"
 "}\n"
 "div.tfp td.support {\n"
 "vertical-align: text-top;\n"
 "border-style: none;\n"
 "background-color: transparent;\n"
 "padding: 1em;\n"
 "margin: 0;\n"
 "}\n"
 "div.tfp td.frame {\n"
 "border-style: none;\n"
 "background-color: transparent;\n"
 "padding: 0.5em 0 0.5em 0;\n"
 "margin: 0;\n"
 "}\n"
 "div.tfp td.frame-top {\n"
 "padding: 0 0 0.5em 0;\n"
 "}\n"
 "div.tfp td.frame-bot {\n"
 "padding: 0.5em 0 0 0;\n"
 "}\n"
 "div.tfp td.status {\n"
 "text-align: center;\n"
 "border: 2px inset #777;\n"
 "background-color: #e7e7e7;\n"
 "}\n"
 "div.tfp td.kids {\n"
 "text-align: center;\n"
 "}\n"
 "div.tfp table.data {\n"
 "border-collapse: collapse;\n"
 "margin: 1em auto;\n"
 "border: 2px solid #777;\n"
 "}\n"
 "div.tfp table.data th {\n"
 "text-align: center;\n"
 "text-weight: bold;\n"
 "background-color: #e7e7e7;\n"
 "padding: 0 0.5em;\n"
 "border: 2px solid #777;\n"
 "}\n"
 "div.tfp table.data td {\n"
 "vertical-align: top;\n"
 "}\n"
 "table.diag td {\n"
 "border-width: 1px 2px;\n"
 "padding: 0 0.5em;\n"
 "margin: 0;\n"
 "white-space: nowrap;\n"
 "}\n"
 "table.diag td.diag {\n"
 "background-color: white;\n"
 "border-width: 0;\n"
 "}\n"
 "table.chart {\n"
 "border-collapse: collapse;\n"
 "margin: 0 auto;\n"
 "}\n"
 "table.chart td {\n"
 "background-color: transparent;\n"
 "border: 0 none;\n"
 "padding: 0;\n"
 "margin: 0;\n"
 "white-space: nowrap;\n"
 "vertical-align: middle;\n"
 "}\n"
 "table.chart td.name {\n"
 "padding: 0 0.5em;\n"
 "}\n"
 "table.property {\n"
 "border-collapse: collapse;\n"
 "margin: 0;\n"
 "}\n"
 "table.property td {\n"
 "background-color: transparent;\n"
 "border: 0 none;\n"
 "padding: 0 0.25em;\n"
 "margin: 0;\n"
 "white-space: nowrap;\n"
 "text-align: left;\n"
 "}\n"
 "table.property td.label {\n"
 "text-align: right;\n"
 "}\n"
 "p.nowrap {\n"
 "white-space: nowrap;\n"
 "}\n"
 "@media print {\n"
 "div.pagesel {\n"
 "display: none;\n"
 "}\n"
 "}\n"
 "div.pagesel {\n"
 "margin: 1em auto;\n"
 "text-align: center;\n"
 "}\n"
 "div.pagesel a {\n"
 "padding: 0.25em 1em;\n"
 "border: 2px solid #777;\n"
 "border-radius: 5px;\n"
 "background-color: yellow;\n"
 "font-size: big;\n"
 "font-weight: bold;\n"
 "white-space: nowrap;\n"
 "}\n"
 "div.pagesel a.pn {\n"
 "padding: 0.25em 0.2em;\n"
 "}\n"
 "div.pagesel a.pncur {\n"
 "background-color: ivory;\n"
 "}\n"
 "div.pagesel a:hover {\n"
 "background-color: orange;\n"
 "}\n"
 "div.pagesel a.pncur:hover {\n"
 "background-color: ivory;\n"
 "text-decoration: none;\n"
 "}\n"
 "div.control a {\n"
 "line-height: 4em;\n"
 "background-color: lightyellow;\n"
 "}\n"
 "div.control a:hover {\n"
 "text-decoration: none;\n"
 "border: 2px solid black;\n"
 "}\n";
static const char s_tab_css[] =  /* tab.css */
 "div.birth { color: #000000; background-color: #ffe8ea; }\n"
 "div.marr  { color: #000000; background-color: #e8ffea; }\n"
 "div.death { color: #000000; background-color: #f0f0f0; }\n"
 "table {\n"
 "margin-left: auto;\n"
 "margin-right: auto;\n"
 "}\n"
 "table td {\n"
 "padding: 1px 0.5em 1px 0.5em;\n"
 "}\n"
 "table.page {\n"
 "color: #000000;\n"
 "background-color: #ffffff;\n"
 "padding: 1em 1em 1em 1em;\n"
 "}\n"
 "table.page td {\n"
 "text-align: center;\n"
 "white-space: nowrap;\n"
 "}\n"
 "table.cert {\n"
 "padding: 1em 1em 1em 1em;\n"
 "}\n"
 "body.marr table.entry {\n"
 "color: #000000;\n"
 "background-color: #d0fce6;\n"
 "border-collapse: collapse;\n"
 "}\n"
 "table.entry {\n"
 "border: 2px solid black;\n"
 "border-collapse: collapse;\n"
 "}\n"
 "table.entry td {\n"
 "border: 1px solid black;\n"
 "}\n"
 "table.entry tr.hd {\n"
 "font-size: x-small;\n"
 "}\n"
 "table.entry td.hd {\n"
 "font-size: x-small;\n"
 "}\n"
 "table.data {\n"
 "border-collapse: collapse;\n"
 "}\n"
 "#tabular-doc {\n"
 "font: normal 1em \"Times New Roman\", serif;\n"
 "}\n"
 "#tabular-doc table.data td {\n"
 "border-top: 2px solid black;\n"
 "border-bottom: 2px solid black;\n"
 "border-left: 1px solid black;\n"
 "border-right: 1px solid black;\n"
 "}\n"
 "#tabular-doc table.data td.hd {\n"
 "border: 1px solid black;\n"
 "}\n"
 "#tabular-doc table.data .hd {\n"
 "font-size: x-small;\n"
 "}\n"
 "#tabular-doc .bigheading {\n"
 "font-size: large;\n"
 "}\n"
 "#tabular-doc table.data td {\n"
 "padding: 0.4em;\n"
 "}\n"
 "#tabular-doc table.data td.lmargin {\n"
 "border: none;\n"
 "border-right: 2px solid black;\n"
 "}\n"
 "#tabular-doc table.data td.rmargin {\n"
 "border: none;\n"
 "border-left: 2px solid black;\n"
 "}\n"
 "#tabular-doc table.data td.tmargin {\n"
 "border-top: 2px solid black;\n"
 "}\n"
 "#tabular-doc table.data td.bmargin {\n"
 "border-bottom: 2px solid black;\n"
 "}\n"
 "table.layout {\n"
 "border-collapse: collapse;\n"
 "border-style: none;\n"
 "border: none;\n"
 "}\n"
 "table.layout td {\n"
 "border-style: none;\n"
 "}\n"
 "#tabular-doc table.data table.layout td {\n"
 "border: none;\n"
 "padding: 0 1em;\n"
 "}\n"
 "#tabular-doc table.data table.layout td.brace {\n"
 "font-size: 2.5em;\n"
 "padding: 0;\n"
 "}\n";

/* End of tfpText.f2c */
