using TMPro;
using UnityEngine;

public class Output : MonoBehaviour
{
    [SerializeField] private Machine m_pMachine = null;
    [SerializeField] private Input m_pNext = null;


    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        m_pMachine = transform.parent.Find("Machine").GetComponent<Machine>(); 
    }
    
    public void OnCollisionEnter(Collision collision)
    {
        Input input = collision.gameObject.GetComponent<Input>();
        Debug.Log(collision.gameObject.name);
        if (input != null)
            m_pNext = input;
    }

    //void OnCollisionExit(Collision collision)
    //{
    //    m_pNext = null;
    //}

    public bool TransferToNext(string type, int amount)
    {
        if(m_pNext == null) return false;

        if (m_pNext.TryInput(type, amount))
            m_pMachine.outputSlot.amount -= amount;
        else
            return false;

        return true;
    }

    // Update is called once per frame
    void Update()
    {
        m_pMachine = transform.parent.Find("Machine").GetComponent<Machine>();

        // Test forcé au lancement : on regarde s'il y a un Input autour de nous (rayon de 0.5m)
        Collider[] hitColliders = Physics.OverlapSphere(transform.position, 0.5f);
        foreach (var hit in hitColliders)
        {
            Input input = hit.GetComponent<Input>();
            if (input != null && hit.gameObject != this.gameObject && input.transform.parent.gameObject != transform.parent.gameObject)
            {
                m_pNext = input;
                Debug.Log("Connexion forcée réussie avec : " + hit.name);
            }
        }

        if (m_pMachine != null && m_pMachine.outputSlot.amount > 0)
        {
            TransferToNext(m_pMachine.outputSlot.type, m_pMachine.outputSlot.amount);
        }
    }
}
