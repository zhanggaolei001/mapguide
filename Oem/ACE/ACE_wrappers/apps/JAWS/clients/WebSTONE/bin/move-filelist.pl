#!/pkg/gnu/bin//perl5
#
#move-filelist.pl,v 1.2 2000/06/04 22:00:03 brunsch Exp
#

push(@INC, "$wd/bin");
require('WebStone-common.pl');

$oldfilelist = "$wd/conf/filelist";

html_begin();

if ($filelist ne $oldfilelist) {
    $backup = $oldfilelist . ".bak";
    print CLIENT "<BODY>Backing up $oldfilelist to $backup";
    rename($oldfilelist, $backup);
    print CLIENT "<P>Copying $filelist to $oldfilelist";
    link($filelist, $oldfilelist);
    print CLIENT "<P>Done.";
}
else
{
    print CLIENT "<STRONG>Can't move $filelist <P>to $filelist</STRONG>";
}

html_end();

# end
