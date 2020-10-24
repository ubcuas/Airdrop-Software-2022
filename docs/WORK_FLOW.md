# Workflow

---

<!-- vscode-markdown-toc -->
* 1. [Issue and Project Tracking](#IssueandProjectTracking)
* 2. [Git Workflow](#GitWorkflow)
	* 2.1. [Master branch](#Masterbranch)
	* 2.2. [Creating a new branch](#Creatinganewbranch)
	* 2.3. [Commit messages](#Commitmessages)
	* 2.4. [Testing](#Testing)
	* 2.5. [Resolve conflicts](#Resolveconflicts)
	* 2.6. [Merge/Pull request (PR)](#MergePullrequestPR)
	* 2.7. [PR review](#PRreview)
* 3. [Example workflow](#Exampleworkflow)

<!-- vscode-markdown-toc-config
	numbering=true
	autoSave=true
	/vscode-markdown-toc-config -->
<!-- /vscode-markdown-toc -->


##  1. <a name='IssueandProjectTracking'></a>Issue and Project Tracking

We will use issue to track our problems and make clear the short term roadmap. Here is a list of the tag we will use for each issue:

| tag name              | priority | meaning                                                      |
| --------------------- | -------- | ------------------------------------------------------------ |
| Bug                   | High     | any problems that cause compilation error or logic error that need to be instantly fixed should be tagged with bug. This could be a feature that needs to be fixed, or need to be added to make the system work again. |
| Testing               | High     |                                                              |
| Feature               | Medium   | features are usually modules that we would like to add to the systems. |
| Maintenance           | Medium   | "features" that we would like to revisit/rewrite.            |
| Design                | Medium   |                                                              |
| CI/CD                 | Low      |                                                              |
| Cleaning/Optimization | Low      | features" that we would like to remove/optimize.             |
| Misc                  | Low      | none technical items such as formatting, documentation edit etc. |

Please note that we the prioritizes are based on High/Low importance and urgency principle. read more about it [here](https://www.mindtools.com/pages/article/newHTE_91.htm).

> It's very important to have details on important issues so that others can understand and recreate the problem. We recommend the issue creator uses one of our templates for issues. 



##  2. <a name='GitWorkflow'></a>Git Workflow

We follow the cetrailized workflow. In a nutshell, we will use `origin/master` as the reference, and have developers create and merge branch from and out 

You are read more about it here:

- [Git workflows](https://www.atlassian.com/git/tutorials/comparing-workflows#centralized-workflow)
- Git tutorials
  - [atlassian](https://www.atlassian.com/git/tutorials/comparing-workflows#centralized-workflow) **(recommended)**. Complete *Getting Started* and *Collaborating* sections.
  - [gitlab](https://docs.gitlab.com/ee/gitlab-basics/)

###  2.1. <a name='Masterbranch'></a>Master branch

This is the "production" branch of our project, and any changes made to it will be thoroughly reviewed and tested. The master branch, or `origin/master` will be tagged with versions that indicates the change/features of the new version, and the `latest` is the version that we will deploy on our integration testing system. There are some key difference between a master branch and a normal branch (development):

- commit history cannot be changed.
- only certain people have access to push to it directly (usually the senior developers, team leads or anyone with Maintainer access).
- normally can only be pushed with Pull requests (see [pull reuqest](#merge/pull-request) section for details).
- is the landing page of the project.
- is where all branches should be checked out from.

###  2.2. <a name='Creatinganewbranch'></a>Creating a new branch

When there is a new issue that you need to work on, you should create a branch from `origin/master`. **Always make sure your branch has a issue with it**, for documentation and progress tracking purpose. The Trello tasks don't need reflect anything regarding to your issue or branch, as it's a higher level milestone oriented tasks. However, if the issue that you are working do not have any Trello task relates to it, you should create a Trello task to reflect what you are working on, so that the team leads can see your updated progress on Trello.

> the name of your branch should be description what the branch is about. It should follow the format `<issue-number>-issue-description`.It should not be too long (`1-fixing-this-that-and-these-with-doing-those`) or too short (`1-fix`). 

Note: Always make sure your local branch is in the remote, and check CI frequently.

###  2.3. <a name='Commitmessages'></a>Commit messages

Commit messages describe what changes have been made. **It should be present tense with verb and noun**. The commit message needs to mention all the important changes so that when a `reset` or `rebase` is needed, we can navigate the commit history with ease. *You are welcomed to use `amend` to clean up your commit history once in a while, but make sure not to accidentally delete changes or over used it.*

###  2.4. <a name='Testing'></a>Testing

TBC

###  2.5. <a name='Resolveconflicts'></a>Resolve conflicts
As you are working on your code on your branch and making commits, you'll want to update your branch with the latest code on `origin/master` to make sure you're working with the latest code. This is important in case someone else merged new code that affects the code you're working on.

To do this, you have 2 options: rebase or merge. [What's the difference?](https://www.atlassian.com/git/tutorials/merging-vs-rebasing). 

Merging is generally recommended, because it is easier to handle conflicts and get stuff working. To merge, simply run `git pull upstream master`.

Rebasing requires more knowledge of git and can cause crazy merge conflicts, so it isn't recommended. You can simply `git pull --rebase upstream master` to rebase your branch onto the latest `upstream/master`.

If you do rebase or merge and get conflicts, you'll need to resolve them manually. [See here for a quick tutorials on what conflicts are and how to resolve them](https://www.atlassian.com/git/tutorials/using-branches/merge-conflicts). Feel free to do this in your IDE or with whatever tool you are most comfortable with. Updating your branch often helps keep conflicts to a minimum, and when they do appear they are usually smaller. Ask for help if you're really stuck!

(borrowed from [UBC-Thunderbots/Software](https://github.com/UBC-Thunderbots/Software/blob/master/docs/workflow.md#updating-your-branch-and-resolving-conflicts))


###  2.6. <a name='MergePullrequestPR'></a>Merge/Pull request (PR)

Pull request is when we merge your changes into `origin/master`. It gave us an opportunity to review and automate test your changes before it gets merged. This workflow will make sure our `origin/master` always compile and bug-free (as much as possible).

Here is an example work flow of a PR:

1. make sure our changes have been made to your issue branch
2. make sure you have [resolved your conflict with `origin/master`](#resolve-conflict), meet the [coding standard](CODE_STANDARD.md) and have [tests](#Testing)
3. check if your branch pass CI. Go to gitlab :arrow_right: CI/CD :arrow_right: Pipelines :arrow_right: Run Pipeline :arrow_right: (select your branch) :arrow_right: Run Pipeline
4. create merge request: Go to gitlab :arrow_right: New Merge Request :arrow_right: (select your branch as source, and choose `origin/master` as the target branch) :arrow_right:  Compare branch and continue.
5. If your branch cannot be automatically merged, please refer to [resolved conflict](#resolve-conflict) section to fixed our PR.
6. **Use the `General`template from Description**
7. Fill in Title, Description, Assignee and Label
8. check the option *Squash commits when merge request is accepted.* 

###  2.7. <a name='PRreview'></a>PR review



##  3. <a name='Exampleworkflow'></a>Example workflow

