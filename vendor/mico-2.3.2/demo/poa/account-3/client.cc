/*
 * Client for our persistent server. In order to demonstrate transparent
 * reactivation of the server (by micod), we explicitly shut down the
 * bank after each operation.
 */

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

  Account_var account = bank->create ("Frank");

  if (CORBA::is_nil (account)) {
    printf ("oops: account is nil\n");
    exit (1);
  }

  bank->shutdown (); // explicit server shutdown

  /*
   * Deposit and withdraw some money
   */

  account->deposit (700);
  bank->shutdown ();

  account->withdraw (450);
  bank->shutdown ();

  printf ("Balance is %ld.\n", account->balance ());
  bank->shutdown ();

  return 0;
}
