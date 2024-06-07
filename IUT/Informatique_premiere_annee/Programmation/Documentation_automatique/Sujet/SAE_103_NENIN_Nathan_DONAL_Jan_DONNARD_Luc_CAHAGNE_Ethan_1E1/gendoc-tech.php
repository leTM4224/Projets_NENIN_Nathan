#!/bin/php
<?php
if (!function_exists('str_starts_with')) {
	function str_starts_with($haystack, $needle) {
		return (string)$needle !== '' && strncmp($haystack, $needle, strlen($needle)) === 0;
	}
}
$fic = fopen("DOC_TECHNIQUE.html", "w");
fwrite($fic,"<!DOCTYPE html>\n");
fwrite($fic,"<html>");
fwrite($fic,"<head>");
fwrite($fic,' <meta charset="utf-8">');
fwrite($fic,"<title>Documentation technique</title>");
fwrite($fic,"</head>");
fwrite($fic,"<body>");
$files = glob("./*.c");
foreach ($files as $nbFile => $file) {
fwrite($fic,'<h1 style="font-size:2.5rem;">'); fwrite($fic,"$file</h1>\n");
$lines = file("$file");
if ($lines[0] == "/**\n") {
	$i = 1;
	while ($lines[$i] != "*/\n") {
		$parts = explode("*", $lines[$i]);
		if (preg_match("/\\\\file/",$parts[1])) {
			$parts = explode('\file ', $parts[1]);
			fwrite($fic,"<p><strong>$parts[1] :</strong></p>\n");
		} elseif (preg_match("/\\\\brief/",$parts[1])) {
			$parts = explode('\brief ', $parts[1]);
			fwrite($fic,"<p>$parts[1]</p>\n");
		} else {
			fwrite($fic,"<p>$parts[1]</p>\n");
		}
		$i = $i + 1;
	}
	fwrite($fic,"<hr>\n");
	fwrite($fic,"<h2>DEFINES</h2>\n");
	foreach ($lines	as $nbLine => $line) {
		if ($line[0] == "*") {
			$parts = explode("*", rtrim($line));
			if (preg_match("/\\\\def/",$parts[1])) {
				$parts = explode("\def ", $parts[1]);
				fwrite($fic,"<p><strong>$parts[1] :</strong></p>\n");
				$parts = explode("\brief ", $lines[$nbLine + 1]);
				fwrite($fic,"<p>$parts[1]</p>\n");
			}
		}
	}

	fwrite($fic,"<hr>\n");
	fwrite($fic,"<h2>STRUCTURES</h2>\n");
	foreach ($lines	as $nbLine => $line) {
		if ($line[0] == "*") {
			$parts = explode("*", rtrim($line));
			if (preg_match("/\\\\struct/",$parts[1])) {
				$parts = explode("\struct ", $parts[1]);
				fwrite($fic,"<h3>$parts[1] :</h3>\n");
				$parts = explode("\brief ", $lines[$nbLine + 1]);
				fwrite($fic,"<p>$parts[1]</p>\n");
				$i = $nbLine + 4;
				while (!preg_match("/}/",$lines[$i])) {
					$parts = explode("/** ", $lines[$i]);
					fwrite($fic,"<p><strong>$parts[0] </strong>");
					$parts = explode("*/", $parts[1]);
					fwrite($fic,"$parts[0]</p>\n");
					$i = $i + 1;
				}
			}
		}
	}

	fwrite($fic,"<hr>\n");
	fwrite($fic,"<h2>GLOBALES</h2>\n");
	foreach ($lines	as $nbLine => $line) {
		$line = rtrim($line);
		if (preg_match('/\/\*\*/',$line) && !str_starts_with($line, '/')) {
			$parts = explode("/*", $line);
			$parts[1] = str_replace("*", "", $parts[1]);
			$parts[1] = str_replace("/", "", $parts[1]);
			fwrite($fic,"<p><strong>$parts[0] </strong>$parts[1]</p>");
		}
	}

	fwrite($fic,"<hr>\n");
	fwrite($fic,"<h2>FONCTIONS</h2>\n");
	foreach ($lines	as $nbLine => $line) {
		if ($line[0] == "*") {
			$parts = explode("*", rtrim($line));
			if (preg_match("/\\\\fn/",$parts[1])) {
				$parts = explode('\fn ', $parts[1]);
				fwrite($fic,"<h3>$parts[1] :</h3>\n");
				if (preg_match("/\\\\brief/",$lines[$nbLine + 1])) {
					$i = $nbLine + 1;
					$lines[$i] = str_replace("\brief ", "", $lines[$i]);
					fwrite($fic,"<p>");
					while (!preg_match("/\\\\/",$lines[$i]) && !preg_match("/\\*\\//",$lines[$i])){
						if ($lines[$i] != "*\n") {
							$lines[$i] = str_replace("*","", $lines[$i]);
							fwrite($fic,"$lines[$i] ");
						}
						$i = $i + 1;
					}
					fwrite($fic,"</p>");
				}
				$i = $nbLine;
				while (!preg_match("/\\*\\//",$lines[$i])) {
					if (preg_match("/\\\\param/",$lines[$i])) {
						$parts = explode("\param ", $lines[$i]);
						$words = explode(" ", $parts[1]);
						$parts = explode($words[1], $parts[1]);
						fwrite($fic,"<p><strong>Parametre : $words[0] $words[1]</strong> $parts[1]</p>\n");
					}
					$i = $i + 1;
				}
				$i = $nbLine;
				while (!preg_match("/\\*\\//",$lines[$i])) {
					if (preg_match("/\\\\return/",$lines[$i])) {
						$parts = explode('\return ', $lines[$i]);
						$words = explode(" ", $parts[1]);
						$parts = explode($words[0], $parts[1]);
						fwrite($fic,"<p><strong>Retourne : $words[0]</strong> $parts[1]</p>\n");
					}
					$i = $i + 1;
				}
			}
		}
	}
	fwrite($fic,"<hr>");
}
}
fwrite($fic,"</body>");
fwrite($fic,"</html>");
fclose($fic);
?>
