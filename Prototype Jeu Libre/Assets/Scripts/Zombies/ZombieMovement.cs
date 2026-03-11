using Unity.VisualScripting;
using UnityEngine;

public class ZombieMovement : MonoBehaviour
{
    [SerializeField] public float m_MinimumSpeed = 0f;
    [SerializeField] public float m_MaximumSpeed = 0f;
    private float m_Speed = 0f;
    private bool m_IsMoving = false;
    private bool m_IsAttacking = false;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        m_Speed = Random.Range(m_MinimumSpeed, m_MaximumSpeed);
    }

    private void OnCollisionEnter(Collision collision)
    {
        Vector3 normal = collision.contacts[0].normal;
        if (Vector3.Dot(normal, new Vector3(0, -1, 0)) == -1)
            m_IsMoving = true;
        else if (Vector3.Dot(normal, new Vector3(0, 0, -1)) == -1)
            m_IsAttacking = true;

    }
    private void OnCollisionExit(Collision collision)
    {
        m_IsAttacking = false;
        m_IsMoving = false;
    }

    void Move()
    {
        Vector3 newPos = transform.position;
        newPos.z -= m_Speed * Time.deltaTime;
        transform.position = newPos;
    }

    void Attack()
    {

    }

    // Update is called once per frame
    void Update()
    {
        if (m_IsMoving && m_IsAttacking == false)
            Move();
        else if (m_IsAttacking)
            Attack();
    }
}
