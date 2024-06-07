#!/bin/php
		<?php
			$out = fopen("DOC_UTILISATEUR.html",'w');
			fwrite($out,"<!DOCTYPE html>");
			fwrite($out,"<html>");
			fwrite($out,"<head>");
			fwrite($out,"<meta charset=\"utf-8\">");
			fwrite($out,"<title>Doc Utilisateur</title>");
			fwrite($out,"</head>");
			fwrite($out,"<body>");
			$file = fopen("DOC_UTILISATEUR.md",'r');
			if (!$file) {
				throw new Exception("DOC_UTILISATEUR.md can't be found\n");
			}
			while ($line = fgets($file)) {
				if ($line[0] == "#") {
					$level = 0;
					for ($i = 0; $i < 4; $i++) {
						if ($line[$i] == "#") {
							$level++;
						}
					}
					$line = str_replace("<","&lt;",$line);
					$line = str_replace(">","&gt;",$line);
					fwrite($out,"<h$level>" . substr($line,$level+1) . "</h$level>");
				}
				elseif (trim($line) == "```") {
					fwrite($out,"<pre><code>");
					while ($line = fgets($file) and trim($line) != "```") {
						$line = str_replace("<","&lt;",$line);
						$line = str_replace(">","&gt;",$line);
						fwrite($out,$line);
					}
					fwrite($out,"</code></pre>");
				}
				elseif ($line[0] == "-" and $line[1] == " ") {
				fwrite($out,"<ul>");
				$curLine = substr($line,2);
				while ($line = fgets($file) and trim($line)) {
					if ($line[0] == "-" and $line[1] == " ") {
						fwrite($out,"<li>" . $curLine . "</li>");
						$curLine = substr($line,2);
					} else {
						$curLine .= $line;
					}
				}
				$curLine = str_replace("<","&lt;",$curLine);
				$curLine = str_replace(">","&gt;",$curLine);
				fwrite($out,"<li>" . $curLine . "</li>");
				fwrite($out,"</ul>");
				}
				elseif ($line[0] == "|" and substr(rtrim($line),-1) == "|") {
				fwrite($out,"<table>");
					$headLine = $line;
					$line = fgets($file);
					$separator = explode("|",rtrim($line));
					$tableLen = count($separator)-2;
					$thead = explode("|",rtrim($headLine));
					$thead = array_splice($thead,1,$tableLen);
					for ($i = 0; $i < $tableLen - (count($thead));$i++) {
						$thead[]="";
					}
					fwrite($out,"<thead>");
					fwrite($out,"<tr>");
					foreach ($thead as $key => $value) {
						fwrite($out,"<th>$value</th>");
					}
					unset($value);
					unset($key);
					fwrite($out,"</tr>");
					fwrite($out,"</thead>");
					fwrite($out,"<tbody>");
					while ($line = fgets($file) and trim($line)) {
						$elements = explode("|",rtrim($line));
						$elements = array_splice($elements,1,$tableLen);
						for ($i = 0; $i < $tableLen - (count($elements));$i++) {
							$elements[]="";
						}
						fwrite($out,"<tr>");
						foreach ($elements as $key => $value) {
							fwrite($out,"<td>$value</td>");
						}
						unset($value);
						unset($key);
						fwrite($out,"</tr>");
					}
					fwrite($out,"</tbody>");
				fwrite($out,"</table>");
				}
				elseif (trim($line)) {
					if (preg_match('/\]\(/',$line)) {
						preg_match_all("/(?=\[).+?(?<=\]\()/",$line, $anchors, PREG_SET_ORDER);
						preg_match_all("/(?=\]\().+?(?<=\))/",$line, $links, PREG_SET_ORDER);
						preg_match_all("/(?=\[).+?(?<=\))/",$line, $needles, PREG_SET_ORDER);
						foreach ($anchors as $key => $value) {
							$a = substr(substr($value[0],1),0, -2);
							$href = substr(substr($links[$key][0],2),0, -1);
							$line = str_replace($needles[$key][0],"<a href=\"$href\">$a</a>",$line);
						}
						unset($value);
						unset($key);
					}
					fwrite($out,"<p>$line</p>");
				}
			}
			fclose($file);
			fwrite($out,"</body>");
			fwrite($out,"</html>");
			fclose($out);
