<!DOCTYPE HTML>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" href="../style.css">
    <title><?php echo (isset($page_title)) ? $page_title : 'Pacman'; ?></title>
</head>
<body>
<div class="Main">
    <br>
    <img src="../logo.png" width="500px">
    <br>
    <br>
    <ul>
        <li class="drop-button">
            <a href="../home.php">Home</a>
        </li>
        <li class="drop-button">
            <?php  // Displays Login/Logout buttons depending on session
                if (isset($_SESSION['user_id'])) {
                    echo "<a href=\"../view_scores.php\">Your Scores</a></li><li class=\"drop-button\"><a href=\"../index.php\">Play Pacman</a></li><li class=\"drop-button\"><a href=\"../login/logout.php\">Logout</a>";
                } else {
                    echo "<a href=\"../login/login_page.php\">Login</a>";
                }
            ?>
    </li>
    </ul>
</div>