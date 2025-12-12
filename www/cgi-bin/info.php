<?php
header("Content-Type: application/json");
echo json_encode([
    "server" => "webserv",
    "status" => "OK",
    "time" => time()
]);
?>
