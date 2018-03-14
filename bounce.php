<?php

$td = 0.05;
$ballCount = 7;
$maxH = 50;

$g = 9.8;
$a = -$g * $td;
$maxV = sqrt($maxH * 2 * $g);

$balls = [];
for ($i = 0; $i < $ballCount; $i++) {
    $balls[$i] = [
        'v' => $maxV * (random_int(50, 100) / 100),
        'h' => 0,
        'c' => chr(random_int(65, 90))
    ];
}

do {
    foreach ($balls as $key => $ball) {
        $v = $ball['v'];
        $h = $ball['h'];

        $h = max(
            0,
            $h + ($v * $td) + (0.5 * $a * $td * $td)
        );

        if ($h === 0) {
            $v = -0.75 * $v;
        }

        $v += $a;

        if ((int) $v === 0 && (int) $h === 0) {
            $v = $maxV * (random_int(90, 100) / 100);
        }

        $balls[$key]['v'] = $v;
        $balls[$key]['h'] = $h;
    }

    system('clear');
    foreach (range($maxH, 1) as $h) {
        foreach ($balls as $ball) {
            if ((int) $ball['h'] === $h) {
                echo $ball['c'].' ';
            }
        }
        echo "\n";
    }

    usleep(10000);
} while (true);

