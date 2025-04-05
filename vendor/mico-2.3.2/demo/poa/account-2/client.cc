#include "account.h"

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

int
main (int argc, char *argv[])
{
  CORBA::ORB_var orb = CORBA::ORB_init (argc, argv);

  /*
   * IOR is in Bank.ref in the local directory
   */

  char pwd[256], uri[300];
  sprintf (uri, "file://%s/Bank.ref", getcwd(pwd, 256));

  /*
   * Connect to the Bank
   */

  CORBA::Object_var obj = orb->string_to_object (uri);
  Bank_var bank = Bank::_narrow (obj);

  if (CORBA::is_nil (bank)) {
    printf ("oops: could not locate Bank\n");
    exit (1);
  }

  /*
   * Open an account
   */

  Account_var account = bank->create ();

  if (CORBA::is_nil (account)) {
    printf ("oops: account is nil\n");
    exit (1);
  }

  /*
   * Deposit and withdraw some money
   */

  account->deposit (700);
  account->withdraw (450);

  printf ("Balance is %ld.\n", account->balance ());

  return 0;
}
